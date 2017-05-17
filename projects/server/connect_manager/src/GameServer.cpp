#include "connect_manager_stdafx.hpp"

GameServer::GameServer(sock_t socket, sockaddr_in_t const &in,
                       std::vector<std::string> const &licences)
    : m_sock(socket), m_port(0), m_in(in), m_licences(licences),
      m_write(false), m_state(State::CONNECTED), m_packet(), m_curClients(0),
      m_maxClients(0), m_ip()
{
  if (::getnameinfo(reinterpret_cast<sockaddr_t *>(&m_in), sizeof(m_in),
                    m_ip.data(), sizeof(m_ip), nullptr, 0,
                    NI_NUMERICHOST | NI_NUMERICSERV) == 0)
    {
      nope::log::Log(Info) << "Client joined " << std::string(m_ip.data());
    }
}

GameServer::GameServer(GameServer &&other)
    : m_sock(std::move(other.m_sock)), m_port(other.m_port),
      m_in(std::move(other.m_in)), m_licences(other.m_licences),
      m_write(other.m_write), m_state(other.m_state),
      m_packet(std::move(other.m_packet)), m_curClients(other.m_curClients),
      m_maxClients(other.m_maxClients), m_ip(other.m_ip)
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
  return (ret);
}

network::IClient::ClientAction GameServer::read(IPacket &pck)
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;

  // Allocate buffer
  std::unique_ptr<std::uint8_t[]> buff =
      std::make_unique<std::uint8_t[]>(packetSize::GameServerToCMPacketSize);
  ssize_t buffLen = 0;

  if (m_sock.rec(buff.get(), packetSize::GameServerToCMPacketSize, &buffLen))
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
	  pck.setData(static_cast<std::size_t>(buffLen), std::move(buff));
	}
    }
  return (ret);
}

bool GameServer::hasTimedOut() const
{
  // TODO: implemented timeout
  return (false);
}

void GameServer::toggleWrite()
{
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
		return (network::IClient::ClientAction::DISCONNECT);
	      }
	    m_port = rep.pck.eventData.licence.port;
	  }
      }
      break;
    case State::AUTHENTICATED:
      nope::log::Log(Info) << "GameServer " << getSocket()
                           << " authenticated."; // TODO: Put here or output ?
      break;
    }
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
      // TODO: To remove
      rep.pck.eventType = GameServerToCMEvent::STRINGIFIED_EVENT;
      GameServerToCMPacketSimple &simple = rep.pck.eventData.string;
      std::memcpy(simple.data.data(), "OK", 3);
      m_packet << rep;
      ret = write(m_packet);
      break;
    }
  if (ret == network::IClient::ClientAction::SUCCESS)
    {
      toggleWrite();
    }
  return (ret);
}

std::array<char, INET6_ADDRSTRLEN> const &GameServer::getIp() const
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