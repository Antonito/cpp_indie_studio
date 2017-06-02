#include "connect_manager_stdafx.hpp"

GameClient::GameClient(sock_t const                       fd,
                       std::vector<GameServerInfo> const &gameServerList,
                       std::mutex &                       gameServerListMut)
    : m_sock(fd), m_write(false), m_state(State::CONNECTED), m_packet(),
      m_gameServerList(gameServerList), m_gameServerListMut(gameServerListMut)
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

  if (m_sock.rec(buff.get(), buffSize, &buffLen))
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
	  pck.setData(static_cast<std::size_t>(buffLen), std::move(buff));
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
		        << "Client requesting game server token";
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

    case State::STATUS:
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
      break;
    case State::STATUS:
#if 0
      {
	// TODO modify the packet to set real info insteab of bebete string
	std::unique_lock<std::mutex> lock(m_gameServerListMut);
	for (std::uint32_t i = 0; i < m_gameServerList.size(); i++)
	  {
	    rep.pck.eventType = GameClientToCMEvent::SERVER_STATUS_EVENT;
	    rep.pck.eventData.status.port = htons(m_gameServerList[i].port);
	    rep.pck.eventData.status.currentClients =
	        htons(m_gameServerList[i].currentClients);
	    rep.pck.eventData.status.maxClients =
	        htons(m_gameServerList[i].maxClients);
	    GameClientToCMPacketIP &simple = rep.pck.eventData.status.ip;
	    std::memcpy(simple.data.data(), m_gameServerList[i].addr.data(),
	                m_gameServerList.size());
	    m_packet << rep;
	    ret = write(m_packet);
	  }
	m_state = State::CONNECTED;
    }
#endif
      break;
    }
  if (ret == network::IClient::ClientAction::SUCCESS)
    {
      toggleWrite();
    }
  return (ret);
}
