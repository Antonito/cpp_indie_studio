#include "game_server_stdafx.hpp"

GameServer::GameServer(std::string const & connectManagerIp,
                       std::uint16_t const cmPort, std::uint16_t const gsPort,
                       std::int32_t const maxClients)
    : m_connectManagerPort(cmPort), m_gameServerPort(gsPort),
      m_maxClients(maxClients), m_curClients(0), m_licence(),
      m_connectManagerSock(m_connectManagerPort, connectManagerIp, true,
                           network::ASocket::SocketType::BLOCKING),
      m_gameSock(
          m_gameServerPort, static_cast<std::uint32_t>(m_maxClients),
          network::ASocket::SocketType::BLOCKING), // TODO: Non-blocking ?
      m_connectSrv(), m_gameSrvTCP(), m_gameSrvUDP(), m_clientList(),
      m_tokenList()
{
  std::ifstream licenceFile(".license");

  if (!licenceFile.is_open())
    {
      nope::log::Log(Error) << "Cannot open file : .license";
      throw std::exception(); // TODO: Real exception
    }
  std::getline(licenceFile, m_licence);
  nope::log::Log(Debug) << "Loaded licence " << m_licence;
  licenceFile.close();

  // Various pre-allocations
  m_clientList.reserve(static_cast<std::size_t>(m_maxClients));
  m_tokenList.reserve(static_cast<std::size_t>(m_maxClients));
}

GameServer::~GameServer()
{
}

bool GameServer::authenticateToConnectManager()
{
  Packet<GameServerToCMPacket> pck;
  GameServerToCMPacket         data;

  nope::log::Log(Debug) << "Connected to ConnectManager";

  // Send "HELLO"
  data.pck.eventType = GameServerToCMEvent::STRINGIFIED_EVENT;
  std::memcpy(data.pck.eventData.string.data.data(), "HELLO", sizeof("HELLO"));

  pck << data;
  if (write(pck) != network::IClient::ClientAction::SUCCESS)
    {
      return (false);
    }

  // Read "WHO ?"
  if (read(pck) != network::IClient::ClientAction::SUCCESS)
    {
      return (false);
    }
  pck >> data;
  if (data.pck.eventType != GameServerToCMEvent::STRINGIFIED_EVENT ||
      std::memcmp(data.pck.eventData.string.data.data(), "WHO ?",
                  sizeof("WHO ?")))
    {
      nope::log::Log(Error) << "Invalid packet received";
      return (false);
    }

  // Send licence + port
  nope::log::Log(Debug) << "Sending licence ...";
  data.pck.eventType = GameServerToCMEvent::LICENCE_EVENT;
  std::memcpy(data.pck.eventData.licence.licence.data.data(),
              m_licence.c_str(), m_licence.length() + 1);
  data.pck.eventData.licence.port = m_gameServerPort;
  pck << data;
  if (write(pck) != network::IClient::ClientAction::SUCCESS)
    {
      return (false);
    }

  // Read "OK"
  if (read(pck) != network::IClient::ClientAction::SUCCESS)
    {
      return (false);
    }
  pck >> data;
  if (data.pck.eventType != GameServerToCMEvent::STRINGIFIED_EVENT ||
      std::memcmp(data.pck.eventData.string.data.data(), "OK", sizeof("OK")))
    {
      nope::log::Log(Error) << "Invalid packet received";
      return (false);
    }
  nope::log::Log(Info) << "Authenticated on connectManager";
  return (true);
}

bool GameServer::run()
{
  nope::log::Log(Debug) << "Running Game Server";
  if (m_connectManagerSock.openConnection() && authenticateToConnectManager())
    {
      // Authenticated to connectManager, shall start gameClient server
      if (m_gameSock.openConnection())
	{
	  nope::log::Log(Info) << "Server started";
	  m_connectSrv = std::thread(&GameServer::connectManagerCom, this);
	  m_gameSrvTCP = std::thread(&GameServer::gameServerTCP, this);
	  m_gameSrvUDP = std::thread(&GameServer::gameServerUDP, this);
	  return (true);
	}
    }
  return (false);
}

void GameServer::stop()
{
  if (m_connectSrv.joinable())
    {
      m_connectSrv.join();
    }
  if (m_gameSrvTCP.joinable())
    {
      m_gameSrvTCP.join();
    }
  if (m_gameSrvUDP.joinable())
    {
      m_gameSrvUDP.join();
    }
}

bool GameServer::addClient()
{
  return (true);
}

bool GameServer::removeClient(network::IClient &)
{
  return (true);
}

bool GameServer::disconnect()
{
  return (true);
}

network::IClient::ClientAction GameServer::write(IPacket const &pck)
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::SUCCESS;
  std::size_t const              sizeToWrite = pck.getSize();
  std::uint8_t const *           data = pck.getData();

  if (m_connectManagerSock.send(data, sizeToWrite) == false)
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

  if (m_connectManagerSock.rec(buff.get(),
                               packetSize::GameServerToCMPacketSize, &buffLen))
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
  // TODO: Implement
  return (false);
}

void GameServer::connectManagerCom()
{
  std::int32_t const sock = m_connectManagerSock.getSocket();
  bool               canWrite = false;

  assert(sock >= 0);
  while (1)
    {
      // Check activity
      fd_set       readfds, writefds, exceptfds;
      std::int32_t rc;

      do
	{
	  struct timeval tv;

	  FD_ZERO(&readfds);
	  FD_ZERO(&writefds);
	  tv.tv_sec = 5;
	  tv.tv_usec = 0;

	  FD_SET(sock, &readfds);
	  if (canWrite)
	    {
	      FD_SET(sock, &writefds);
	    }
	  exceptfds = readfds;
	  rc = select(sock + 1, &readfds, &writefds, &exceptfds, &tv);
	}
      while (rc == -1 && errno == EINTR);

      // Treat data
      if (rc < 0)
	{
	  // There was an error
	  nope::log::Log(Error) << "select() failed [ConnectManager]";
	  break;
	}
      else if (rc > 0)
	{
	  if (FD_ISSET(sock, &readfds))
	    {
	      // Treat input
	    }
	  if (canWrite && FD_ISSET(sock, &writefds))
	    {
	      // Treat output
	    }
	  if (FD_ISSET(sock, &exceptfds))
	    {
	      nope::log::Log(Error) << "Something happened";
	      break;
	    }
	}
    }
  nope::log::Log(Info) << "Connection with license server closed.";
}

void GameServer::gameServerTCP()
{
  std::int32_t const sock = m_gameSock.getSocket();
  bool               canWrite = false;

  assert(sock >= 0);
  while (1)
    {
      // Check activity
      fd_set       readfds, writefds, exceptfds;
      std::int32_t rc;

      do
	{
	  struct timeval tv;
	  std::int32_t   maxSock = sock;

	  FD_ZERO(&readfds);
	  FD_ZERO(&writefds);
	  tv.tv_sec = 5;
	  tv.tv_usec = 0;

	  FD_SET(sock, &readfds);
	  if (canWrite)
	    {
	      FD_SET(sock, &writefds);
	    }
	  // TODO: Add clients

	  exceptfds = readfds;
	  rc = select(maxSock + 1, &readfds, &writefds, &exceptfds, &tv);
	}
      while (rc == -1 && errno == EINTR);

      if (rc < 0)
	{
	  // There was an error
	  nope::log::Log(Error) << "select() failed [TCP]";
	  break;
	}
      else if (rc > 0)
	{
	}
    }
}

void GameServer::gameServerUDP()
{
  // TODO: Open UDP connection
}
