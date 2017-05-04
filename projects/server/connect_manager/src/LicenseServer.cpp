#include "connect_manager_stdafx.hpp"

constexpr std::uint32_t LicenseServer::maxGameServer;

LicenseServer::LicenseServer(std::uint16_t const licensePort,
                             std::uint16_t const gameServerPort)
    : m_license(licensePort, "localhost", false, network::ASocket::BLOCKING),
      m_gameServer(gameServerPort, LicenseServer::maxGameServer,
                   network::ASocket::BLOCKING),
      m_licenseList(), m_gameServerList(), m_thread(), m_cond(), m_mut()
{
}

LicenseServer::~LicenseServer()
{
}

bool LicenseServer::run()
{
  nope::log::Log(Debug) << "Running server";
  if (m_license.openConnection())
    {
      nope::log::Log(Debug) << "Connection opened";
      if (m_gameServer.openConnection())
	{
	  nope::log::Log(Debug) << "GameServer's server opened";
	  m_thread = std::thread([&]() { this->_loop(); });
	  return (true);
	}
    }
  nope::log::Log(Error) << "Cannot open connection";
  return (false);
}

void LicenseServer::stop()
{
  if (m_thread.joinable())
    {
      m_thread.join();
    }
}

bool LicenseServer::addClient()
{
  return (true);
}

bool LicenseServer::removeClient(network::IClient &c)
{
  GameServer &g = static_cast<GameServer &>(c);

  nope::log::Log(Debug) << "Removing client";
  g.disconnect();
  m_gameServerList.erase(
      std::remove_if(
          m_gameServerList.begin(), m_gameServerList.end(),
          [&](std::unique_ptr<GameServer> const &o) { return (*o == g); }),
      m_gameServerList.end());
  return (true);
}

void LicenseServer::waitSignal()
{
  std::unique_lock<std::mutex> lock(m_mut);
  m_cond.wait(lock);
}

void LicenseServer::_loop()
{
  bool monitorLicenseServer = true;

  nope::log::Log(Debug) << "Loading licenses";
  loadLicenses();
  nope::log::Log(Info) << "Loaded licenses.";

  // Create gameServer's server
  m_mut.lock();
  m_cond.notify_one();
  m_mut.unlock();
  nope::log::Log(Debug) << "Getting game socket";
  std::int32_t gameSocket = m_gameServer.getSocket();

  if (gameSocket == -1)
    {
      throw network::SockError("Cannot create game server socket");
    }

  // Resize vector to max client
  m_gameServerList.reserve(maxGameServer);

  nope::log::Log(Debug) << "Starting to loop";
  while (1)
    {
      std::int32_t   rc = -1;
      fd_set         readfds, writefds, exceptfds;
      struct timeval tv;
      std::int32_t   maxFd;

      // Check file descriptors
      do
	{
	  FD_ZERO(&readfds);
	  FD_ZERO(&writefds);
	  FD_ZERO(&exceptfds);
	  tv.tv_sec = 2;
	  tv.tv_usec = 0;

	  // Add license manager's socket if needed
	  maxFd = (monitorLicenseServer) ? m_license.getSocket() : 0;
	  assert(maxFd != -1);
	  if (monitorLicenseServer)
	    {
	      FD_SET(maxFd, &readfds);
	    }
	  // Add Game Server's socket
	  maxFd = (gameSocket > maxFd) ? gameSocket : maxFd;
	  FD_SET(gameSocket, &readfds);

	  // Add every GameServer to the file descriptor list
	  for (std::unique_ptr<GameServer> const &game : m_gameServerList)
	    {
	      std::int32_t sock = game->getSocket();

	      if (sock > 0)
		{
		  nope::log::Log(Debug) << "Adding to readfds: #" << sock;
		  FD_SET(sock, &readfds);
		  // Add it to the writefds set if you can
		  if (game->canWrite())
		    {
		      FD_SET(sock, &writefds);
		    }

		  // Update max file descriptor
		  if (sock > maxFd)
		    {
		      maxFd = sock;
		    }
		}
	    }

	  // Loop over gameServers
	  rc = select(maxFd + 1, &readfds, &writefds, &exceptfds, &tv);
	}
      while (rc == -1 && errno == EINTR);

      if (rc < 0)
	{
	  // There was an error
	  nope::log::Log(Error) << "select() failed";
	  break;
	}
      else if (rc > 0)
	{
	  // Handle IO
	  if (FD_ISSET(m_license.getSocket(), &readfds))
	    {
	      std::array<char, 400> arr; // TODO: Change
	      ssize_t readVal;

	      if (m_license.rec(arr.data(), 400, &readVal))
		{
		  if (readVal == 0)
		    {
		      break;
		    }
		  arr[static_cast<std::size_t>(readVal)] = '\0';
		  std::cout << std::string(arr.data()) << std::endl;
		  loadLicenses();
		}
	      else
		{
		  // Nothing more to read, byebye
		  break;
		}
	    }

	  if (FD_ISSET(gameSocket, &readfds))
	    {
	      // Accept new client
	      std::int32_t  _rc = 0;
	      sockaddr_in_t in = {};

	      nope::log::Log(Debug) << "There's client to accept on socket #"
	                            << gameSocket;
	      do
		{
		  socklen_t len = sizeof(in);
		  _rc = ::accept(gameSocket,
		                 reinterpret_cast<sockaddr_t *>(&in), &len);
		}
	      while (_rc == -1 && errno == EINTR);

	      // Check if the socket is valid
	      if (rc > 0)
		{
		  m_gameServerList.push_back(
		      std::make_unique<GameServer>(_rc, in));
		  nope::log::Log(Debug)
		      << "Added client FD #"
		      << m_gameServerList.back()->getSocket();
		}
	    }

	  // Loop over gameServers and handle IO
	  nope::log::Log(Debug) << "Checking GameServer's IO";
	  for (std::vector<std::unique_ptr<GameServer>>::iterator iter =
	           m_gameServerList.begin();
	       iter != m_gameServerList.end();)
	    {
	      bool                         deleted = false;
	      std::unique_ptr<GameServer> &game = *iter;
	      sock_t                       sock = game->getSocket();

	      if (FD_ISSET(sock, &readfds))
		{
		  network::IClient::ClientAction action;

		  nope::log::Log(Debug) << "Can write to socket #" << sock;
		  action = game->read();
		  if (action == network::IClient::ClientAction::DISCONNECT)
		    {
		      removeClient(*game);
		      deleted = true;
		    }
		}
	      if (deleted == false && FD_ISSET(sock, &writefds))
		{
		  // TODO: Write
		}
	      if (deleted == false && FD_ISSET(sock, &exceptfds))
		{
		  // TODO: Except
		}

	      // Check if we deleted anything
	      if (!deleted)
		++iter;
	    }
	}
    }
  nope::log::Log(Debug) << "Stopped server loop";
}

bool LicenseServer::loadLicenses()
{
  std::ifstream licensesFile(".license_keys");

  if (licensesFile.is_open())
    {
      // Add each key the key list
      std::string license;
      while (std::getline(licensesFile, license))
	{
	  if (std::find(m_licenseList.begin(), m_licenseList.end(), license) ==
	      m_licenseList.end())
	    {
	      m_licenseList.push_back(license);
	      nope::log::Log(Info) << "Adding key: " << license;
	    }
	}
      licensesFile.close();
      return (true);
    }
  return (false);
}

// GameServer definition
LicenseServer::GameServer::GameServer(sock_t socket, sockaddr_in_t const &in)
    : m_sock(socket), m_in(in)
{
  std::array<char, INET6_ADDRSTRLEN> clntName;

  if (::getnameinfo(reinterpret_cast<sockaddr_t *>(&m_in), sizeof(m_in),
                    clntName.data(), sizeof(clntName), nullptr, 0,
                    NI_NUMERICHOST | NI_NUMERICSERV) == 0)
    {
      nope::log::Log(Info) << "Client joined " << std::string(clntName.data())
                           << std::endl;
    }
}

LicenseServer::GameServer::GameServer(GameServer &&other)
    : m_sock(std::move(other.m_sock)), m_in(std::move(other.m_in))
{
}

sock_t LicenseServer::GameServer::getSocket() const
{
  return (m_sock.getSocket());
}

bool LicenseServer::GameServer::canWrite() const
{
  // TODO: Implement
  return (false);
}

bool LicenseServer::GameServer::disconnect()
{
  nope::log::Log(Debug) << "Client disconnected #" << getSocket();
  m_sock.closeConnection();
  return (true);
}

network::IClient::ClientAction LicenseServer::GameServer::write()
{
  return (network::IClient::ClientAction::DISCONNECT);
}

network::IClient::ClientAction LicenseServer::GameServer::read()
{
  return (network::IClient::ClientAction::DISCONNECT);
}

bool LicenseServer::GameServer::hasTimedOut() const
{
  return (false);
}

bool LicenseServer::GameServer::
    operator==(LicenseServer::GameServer const &other) const
{
  if (this != &other)
    {
      return (m_sock == other.m_sock);
    }
  return (true);
}
