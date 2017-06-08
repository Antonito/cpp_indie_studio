#include "connect_manager_stdafx.hpp"

GameServer::GameServer(sock_t socket, sockaddr_in_t const &in,
                       std::string const &publicIp, bool const allowInternet,
                       std::vector<std::string> const &licences)
    : m_sock(socket), m_port(0), m_in(in), m_licences(licences),
      m_write(false), m_state(State::CONNECTED), m_packet(), m_curClients(0),
      m_maxClients(0), m_ip(), m_token(), m_tokenTreating(),
      m_lastAction(std::chrono::system_clock::now())
{
  if (::getnameinfo(reinterpret_cast<sockaddr_t *>(&m_in), sizeof(m_in),
                    m_ip.data(), sizeof(m_ip), nullptr, 0,
                    NI_NUMERICHOST | NI_NUMERICSERV) == 0)
    {
      std::string const ipStr(m_ip.data());

      if (allowInternet && ipStr == "127.0.0.1")
	{
	  nope::log::Log(Debug)
	      << "Local address detected, switching to internet one ["
	      << publicIp << "]";
	  assert(publicIp.length() <= INET6_ADDRSTRLEN_INDIE_INDIE_INDIE);
	  m_ip.fill('\0');
	  std::memcpy(m_ip.data(), publicIp.c_str(), publicIp.length());
	}
      nope::log::Log(Info) << "Client joined " << std::string(m_ip.data());
    }
}

GameServer::GameServer(GameServer &&other)
    : m_sock(std::move(other.m_sock)), m_port(other.m_port),
      m_in(std::move(other.m_in)), m_licences(other.m_licences),
      m_write(other.m_write), m_state(other.m_state),
      m_packet(std::move(other.m_packet)), m_curClients(other.m_curClients),
      m_maxClients(other.m_maxClients), m_ip(other.m_ip),
      m_token(other.m_token), m_tokenTreating(other.m_tokenTreating),
      m_lastAction(other.m_lastAction)
{
}

sock_t GameServer::getSocket() const
{
  return (m_sock.getSocket());
}

bool GameServer::canWrite() const
{
  return (m_write);
}

bool GameServer::disconnect()
{
  updateLastAction();
  nope::log::Log(Debug) << "Client disconnected #" << getSocket();
  m_sock.closeConnection();
  return (true);
}

network::IClient::ClientAction GameServer::write(IPacket const &pck)
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::SUCCESS;
  std::size_t const              sizeToWrite = pck.getSize();
  std::uint8_t const *           data = pck.getData();

  if (m_sock.send(data, sizeToWrite) == false)
    {
      nope::log::Log(Debug) << "Failed to write data [GameServer]";
      ret = network::IClient::ClientAction::FAILURE;
    }
  updateLastAction();
  return (ret);
}

network::IClient::ClientAction GameServer::read(IPacket &pck)
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;

  // Allocate buffer
  std::unique_ptr<std::uint8_t[]> buff =
      std::make_unique<std::uint8_t[]>(packetSize::GameServerToCMPacketSize);
  ssize_t headerLen = 0;
  ssize_t buffLen = 0;

  // Read header first
  if (m_sock.rec(buff.get(), sizeof(PacketHeader), &headerLen))
    {
      assert(headerLen >= 0);
      if (headerLen == 0)
	{
	  nope::log::Log(Debug)
	      << "Read failed, shall disconnect [GameServer Header]";
	  ret = network::IClient::ClientAction::DISCONNECT;
	}
      else
	{
	  nope::log::Log(Debug) << "Received header, checking it [GameServer]";
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
	          << "Should read " << sizeToRead << "[GameServer]";
	      if (static_cast<std::size_t>(headerLen + sizeToRead) <=
	          packetSize::GameServerToCMPacketSize)
		{
		  // Read rest of the packet
		  if (m_sock.rec(buff.get() + headerLen, sizeToRead, &buffLen))
		    {
		      assert(buffLen >= 0);
		      if (buffLen == 0)
			{
			  nope::log::Log(Debug)
			      << "Read failed, shall disconnect [GameServer]";
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
	      else
		{
		  nope::log::Log(Debug)
		      << "Invalid packet received [GameServer]";
		  ret = network::IClient::ClientAction::DISCONNECT;
		}
	    }
	}
    }

  updateLastAction();
  return (ret);
}

bool GameServer::hasTimedOut() const
{
  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

  if (std::chrono::duration_cast<std::chrono::seconds>(now - m_lastAction)
          .count() >= 2)
    {
      return (true);
    }
  return (false);
}

void GameServer::toggleWrite()
{
  updateLastAction();
  m_write = !m_write;
}

bool GameServer::operator==(GameServer const &other) const
{
  if (this != &other)
    {
      return (m_sock == other.m_sock);
    }
  return (true);
}

network::IClient::ClientAction GameServer::treatIncomingData()
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;
  GameServerToCMPacket           rep;

  switch (m_state)
    {
    case State::CONNECTED:
      {
	ret = read(m_packet);
	nope::log::Log(Debug) << "Reading in state CONNECTED [GameServer]";
	if (ret == network::IClient::ClientAction::SUCCESS)
	  {
	    m_packet >> rep;
	    if (std::memcmp(&rep.pck.eventData.string, "HELLO", 5) != 0)
	      {
		nope::log::Log(Debug) << "Error in state CONNECTED, invalid "
		                         "payload, shall disconnect "
		                         "[GameServer]";
		return (network::IClient::ClientAction::DISCONNECT);
	      }
	  }
      }
      break;
    case State::SETTING:
      {
	ret = read(m_packet);
	nope::log::Log(Debug) << "Reading in state SETTING [GameServer]";
	if (ret == network::IClient::ClientAction::SUCCESS)
	  {
	    m_packet >> rep;
	    if (std::find(m_licences.begin(), m_licences.end(),
	                  rep.pck.eventData.licence.licence.data.data()) ==
	        m_licences.end())
	      {
		nope::log::Log(Debug) << "Error in state SETTING, invalid "
		                         "payload, shall disconnect "
		                         "[GameServer]";
		nope::log::Log(Info) << "License is invalid.";
		return (network::IClient::ClientAction::DISCONNECT);
	      }
	    m_port = rep.pck.eventData.licence.port;
	  }
      }
      break;
    case State::AUTHENTICATED:
      nope::log::Log(Info)
          << "GameServer " << getSocket()
          << " in authenticated state."; // TODO: Put here or output ?
      break;
    case State::TOKEN:
      {
	multithread::ResultGetter<TokenCom> &token = m_tokenTreating.front();

	nope::log::Log(Debug)
	    << "Reading Token response from distant game server";
	ret = read(m_packet);
	token.getData().treated = 0;
	if (ret == network::IClient::ClientAction::SUCCESS)
	  {
	    // Got a token from the gameServer !
	    m_packet >> rep;
	    if (rep.pck.eventType == GameServerToCMEvent::TOKEN)
	      {
		// Got a packet !
		token.getData().treated = rep.pck.eventData.token.treated;
		token.getData().port = rep.pck.eventData.token.port;
		token.getData().tokenData = rep.pck.eventData.token.tokenData;
		nope::log::Log(Info)
		    << "Received token from distant game server !";
	      }
	    else
	      {
		nope::log::Log(Warning)
		    << "Invalid packet received, expected token.";
	      }
	  }

	// Send it back to the game client
	m_tokenTreating.pop();
	token.notify();
	m_state = State::AUTHENTICATED;
      }
      break;
    }

  // Update IO
  if (ret == network::IClient::ClientAction::SUCCESS)
    {
      toggleWrite();
    }
  return (ret);
}

network::IClient::ClientAction GameServer::treatOutcomingData()
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;

  GameServerToCMPacket rep;
  switch (m_state)
    {
    case State::CONNECTED:
      {
	rep.pck.eventType = GameServerToCMEvent::STRINGIFIED_EVENT;
	GameServerToCMPacketSimple &simple = rep.pck.eventData.string;
	std::memcpy(simple.data.data(), "WHO ?", 6);
	m_packet << rep;
	ret = write(m_packet);
	nope::log::Log(Debug) << "Switching to state SETTING [GameServer]";
	m_state = State::SETTING;
      }
      break;
    case State::SETTING:
      {
	rep.pck.eventType = GameServerToCMEvent::STRINGIFIED_EVENT;
	GameServerToCMPacketSimple &simple = rep.pck.eventData.string;
	std::memcpy(simple.data.data(), "OK", 3);
	m_packet << rep;
	ret = write(m_packet);
	nope::log::Log(Debug)
	    << "Switching to state AUTHENTICATED [GameServer]";
	m_state = State::AUTHENTICATED;
      }
      break;
    case State::AUTHENTICATED:
      if (!m_token.size())
	{
	  // Return to read mode
	  ret = network::IClient::ClientAction::SUCCESS;
	  break;
	}
      nope::log::Log(Debug) << "There are pending token requests";
      m_state = State::TOKEN;

// Allow fall through
#if defined(__clang__)
      [[clang::fallthrough]];
#elif defined(__GNUC__)
      __attribute__((fallthrough));
#endif

    case State::TOKEN:
      nope::log::Log(Debug) << "Sending Token request to distant game server";
      rep.pck.eventType = GameServerToCMEvent::REQUEST_TOKEN;
      m_packet << rep;
      ret = write(m_packet);
      if (ret == network::IClient::ClientAction::SUCCESS)
	{
	  // Transfering requests, prevent from treating twice the same request
	  nope::log::Log(Debug) << "Request sent, transfering request ...";
	  m_tokenTreating.push(m_token.front());
	  m_token.pop();
	}
      break;
    }

  // Update IO
  if (ret == network::IClient::ClientAction::SUCCESS)
    {
      toggleWrite();
    }
  return (ret);
}

std::array<char, INET6_ADDRSTRLEN_INDIE> const &GameServer::getIp() const
{
  return (m_ip);
}

std::uint16_t GameServer::getPort() const
{
  return (m_port);
}

std::uint16_t GameServer::getCurrentClients() const
{
  return (m_curClients);
}

std::uint16_t GameServer::getMaxClients() const
{
  return (m_maxClients);
}

bool GameServer::isRequested(TokenCom const &tok) const
{
  return (tok.port == m_port && tok.ip == m_ip);
}

void GameServer::pushRequest(multithread::ResultGetter<TokenCom> &tok)
{
  m_token.push(tok);
}

bool GameServer::hasRequests() const
{
  return (m_token.size() != 0);
}

void GameServer::updateLastAction()
{
  nope::log::Log(Debug) << "Updating last action";
  m_lastAction = std::chrono::system_clock::now();
}
