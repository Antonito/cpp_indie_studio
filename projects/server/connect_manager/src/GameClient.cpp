#include "connect_manager_stdafx.hpp"

GameClient::GameClient(
    sock_t const fd, std::vector<GameServerInfo> const &gameServerList,
    std::mutex &                                             gameServerListMut,
    multithread::Queue<multithread::ResultGetter<TokenCom>> &token)
    : m_sock(fd), m_write(false), m_state(State::CONNECTED), m_packet(),
      m_gameServerList(gameServerList), m_gameServerListMut(gameServerListMut),
      m_token(token), m_requIp(), m_requPort()
{
}

GameClient::~GameClient()
{
}

bool GameClient::disconnect()
{
  nope::log::Log(Debug) << "GameClient disconnected #" << getSocket();
  m_sock.closeConnection();
  return (true);
}

network::IClient::ClientAction GameClient::write(IPacket const &pck)
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::SUCCESS;
  std::size_t const              sizeToWrite = pck.getSize();
  std::uint8_t const *           data = pck.getData();

  if (m_sock.send(data, sizeToWrite) == false)
    {
      nope::log::Log(Debug) << "Failed to write data [GameClient]";
      ret = network::IClient::ClientAction::FAILURE;
    }
  return (ret);
}

network::IClient::ClientAction GameClient::read(IPacket &pck)
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;
  std::size_t const buffSize = packetSize::GameClientToCMPacketSize;

  // Allocate buffer
  std::unique_ptr<uint8_t[]> buff = std::make_unique<std::uint8_t[]>(buffSize);
  ssize_t                    buffLen = 0;
  ssize_t                    headerLen = 0;

  // Read header first
  if (m_sock.rec(buff.get(), sizeof(PacketHeader), &headerLen))
    {
      assert(headerLen >= 0);
      if (headerLen == 0)
	{
	  nope::log::Log(Debug)
	      << "Read failed, shall disconnect [GameClient Header]";
	  ret = network::IClient::ClientAction::DISCONNECT;
	}
      else
	{
	  nope::log::Log(Debug) << "Received header, checking it [GameClient]";
	  // Check header
	  PacketHeader *header = reinterpret_cast<PacketHeader *>(buff.get());

	  header->magic.magic = ntohs(header->magic.magic);
	  std::uint8_t vers = header->getVersion();
	  std::uint8_t magic = header->getMagic();
	  header->magic.magic = htons(header->magic.magic);
	  if (vers == PacketHeader::Version && magic == PacketHeader::Magic)
	    {
	      // Get size to read
	      std::uint16_t sizeToRead = ntohs(header->size);

	      nope::log::Log(Debug)
	          << "Should read " << sizeToRead << "[GameClient]";

	      if (m_sock.rec(buff.get() + headerLen, sizeToRead, &buffLen))
		{
		  assert(buffLen >= 0);
		  if (buffLen == 0)
		    {
		      nope::log::Log(Debug)
		          << "Read failed, shall disconnect [GameClient]";
		      ret = network::IClient::ClientAction::DISCONNECT;
		    }
		  else
		    {
		      ret = network::IClient::ClientAction::SUCCESS;
		      pck.setData(
		          static_cast<std::size_t>(buffLen + headerLen),
		          std::move(buff));
		    }
		}
	    }
	}
    }
  return (ret);
}

bool GameClient::hasTimedOut() const
{
  // TODO : implemented timeout
  return (false);
}

bool GameClient::operator==(GameClient const &other) const
{
  if (this != &other)
    {
      return (m_sock == other.m_sock);
    }
  return (true);
}

std::int32_t GameClient::getSocket() const
{
  return (m_sock.getSocket());
}

bool GameClient::canWrite() const
{
  return (m_write);
}

void GameClient::toggleWrite()
{
  m_write = !m_write;
}

network::IClient::ClientAction GameClient::treatIncomingData()
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;
  GameClientToCMPacket           rep;

  switch (m_state)
    {
    case State::CONNECTED:
      {
	ret = read(m_packet);
	nope::log::Log(Debug) << "Reading in state CONNECTED [GameClient]";

	if (ret == network::IClient::ClientAction::SUCCESS)
	  {
	    m_packet >> rep;
	    // What did the client request ?
	    if (rep.pck.eventType == GameClientToCMEvent::REQUEST_EVENT)
	      {
		if (rep.pck.eventData.intEvent.event ==
		    static_cast<std::uint16_t>(
		        GameClientToCMPacketSimpleEvent::LIST_SERVERS))
		  {
		    // Switching to state REQU_LIST_SERV
		    nope::log::Log(Info)
		        << "Client requesting game server list";
		    m_state = State::REQU_LIST_SERV;
		  }
		else if (rep.pck.eventData.intEvent.event ==
		         static_cast<std::uint16_t>(
		             GameClientToCMPacketSimpleEvent::GET_TOKEN))
		  {
		    // Switching to state GET_TOKEN
		    nope::log::Log(Info)
		        << "Client requesting game server token { "
		        << std::string(
		               rep.pck.eventData.tokenRequ.ip.data.data())
		        << ":" << rep.pck.eventData.tokenRequ.port << " }";
		    m_requIp = rep.pck.eventData.tokenRequ.ip.data;
		    m_requPort = rep.pck.eventData.tokenRequ.port;
		    m_state = State::REQU_TOKEN;
		  }
		else
		  {
		    // Unknown request, try again
		    nope::log::Log(Warning) << "Client : unsupported request.";
		    ret = network::IClient::ClientAction::FAILURE;
		  }
	      }
	    else
	      {
		nope::log::Log(Debug) << "Error in state CONNECTED, invalid "
		                         "payload, shall disconnect "
		                         "[GameClient]";
		return (network::IClient::ClientAction::DISCONNECT);
	      }
	  }
      }
      break;

    // This should never happen
    case State::REQU_LIST_SERV:
      assert(0);
      break;
    case State::REQU_TOKEN:
      assert(0);
      break;
    }
  if (ret == network::IClient::ClientAction::SUCCESS)
    {
      toggleWrite();
    }
  return (ret);
}

network::IClient::ClientAction
    GameClient::_listServers(GameClientToCMPacket &rep)
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;

  std::unique_lock<std::mutex> lock(m_gameServerListMut);

  // Get server's infos
  rep.pck.eventType = GameClientToCMEvent::LIST_SERVERS_EVENT;

  rep.pck.eventData.serverList.nbServers =
      static_cast<std::int32_t>(m_gameServerList.size());
  rep.pck.eventData.serverList.nbServers =
      std::min(rep.pck.eventData.serverList.nbServers,
               GameClientToCMPacketServerList::maxServers);
  nope::log::Log(Debug) << "There are "
                        << rep.pck.eventData.serverList.nbServers
                        << " game servers.";
  if (rep.pck.eventData.serverList.nbServers)
    {
      // Fill serverListPtr
      for (std::size_t i = 0; i < m_gameServerList.size(); ++i)
	{
	  GameServerInfo const &cur = m_gameServerList[i];
	  nope::log::Log(Debug)
	      << "Server #" << i << ": " << std::string(cur.addr.data()) << ":"
	      << cur.port << " [ " << cur.currentClients << " / "
	      << cur.maxClients << " ]";
	  rep.pck.eventData.serverList.servers[i].ip.data = cur.addr;
	  rep.pck.eventData.serverList.servers[i].port = cur.port;
	  rep.pck.eventData.serverList.servers[i].currentClients =
	      cur.currentClients;
	  rep.pck.eventData.serverList.servers[i].maxClients = cur.maxClients;
	}
    }

  // Send packet
  m_packet << rep;
  ret = write(m_packet);

  // Display some infos
  if (ret == network::IClient::ClientAction::SUCCESS)
    {
      nope::log::Log(Info) << "GameClient " << getSocket()
                           << " ServerList sent.";
    }
  else
    {
      nope::log::Log(Error)
          << "GameClient " << getSocket() << " cannot send serverList.";
    }
  m_state = State::CONNECTED; // Wait for more commands
  return (ret);
}

network::IClient::ClientAction
    GameClient::_requToken(GameClientToCMPacket &rep)
{
  network::IClient::ClientAction      ret;
  TokenCom                            tokenRaw = {};
  multithread::ResultGetter<TokenCom> tokenRequ(tokenRaw);

  // Set request's data
  tokenRaw.ip = m_requIp;
  tokenRaw.port = m_requPort;
  nope::log::Log(Debug) << "Pushing token request";
  m_token.push(tokenRequ);
  nope::log::Log(Debug) << "Waiting for token response";
  tokenRequ.waitForNotif();

  nope::log::Log(Debug) << "Got token response";
  std::unique_lock<std::mutex> lock(tokenRequ.getMut());
  nope::log::Log(Debug) << "Locked token response";
  TokenCom const &tok = tokenRequ.getData();
  rep.pck.eventType = GameClientToCMEvent::GET_TOKEN_EVENT;
  rep.pck.eventData.token.valid = static_cast<std::uint16_t>(tok.treated);
  rep.pck.eventData.token.data = tok.tokenData;
  nope::log::Log(Debug) << "RECEIVED ---> Treated: " << tok.treated;
  m_packet << rep;
  nope::log::Log(Debug) << "Sending token response";
  ret = write(m_packet);

  // Display some infos
  if (ret == network::IClient::ClientAction::SUCCESS)
    {
      nope::log::Log(Info) << "GameClient " << getSocket() << " token sent.";
    }
  else
    {
      nope::log::Log(Error)
          << "GameClient " << getSocket() << " cannot send token.";
    }

  // Reset requests
  m_requIp.fill('\0');
  m_requPort = 0;

  m_state = State::CONNECTED; // Wait for more commands
  return (ret);
}

network::IClient::ClientAction GameClient::treatOutcomingData()
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;
  GameClientToCMPacket           rep = {};

  switch (m_state)
    {
    case State::CONNECTED:
      break;
    case State::REQU_LIST_SERV:
      ret = _listServers(rep);
      break;
    case State::REQU_TOKEN:
      ret = _requToken(rep);
      break;
    }
  if (ret == network::IClient::ClientAction::SUCCESS)
    {
      toggleWrite();
    }
  return (ret);
}
