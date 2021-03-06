#include "connect_manager_stdafx.hpp"

constexpr std::uint32_t LicenseServer::maxGameServer;

LicenseServer::LicenseServer(
    std::uint16_t const licensePort, std::uint16_t const gameServerPort,
    std::string const &publicIp, bool const allowInternetAccess,
    multithread::Queue<multithread::ResultGetter<TokenCom>> &token)
    : m_license(licensePort, "localhost", false, network::ASocket::BLOCKING),
      m_gameServer(gameServerPort, LicenseServer::maxGameServer,
                   network::ASocket::BLOCKING),
      m_licenseList(), m_gameServerList(), m_thread(), m_cond(), m_mut(),
      m_list(), m_gameServerListMut(), m_publicIp(publicIp),
      m_allowInternet(allowInternetAccess), m_token(token)
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
  // Accept new client
  std::int32_t  rc = 0;
  sockaddr_in_t in = {};
  sock_t const  gameSocket = m_gameServer.getSocket();

  nope::log::Log(Debug) << "There's client to accept on socket #"
                        << gameSocket;
  do
    {
      socklen_t len = sizeof(in);
      rc = ::accept(gameSocket, reinterpret_cast<sockaddr_t *>(&in), &len);
    }
  while (rc == -1 && errno == EINTR);

  // Check if the socket is valid
  if (rc > 0)
    {
      m_gameServerList.push_back(std::make_unique<GameServer>(
          rc, in, m_publicIp, m_allowInternet, m_licenseList));
      nope::log::Log(Debug)
          << "Added client FD #" << m_gameServerList.back()->getSocket();
      return (true);
    }
  return (false);
}

bool LicenseServer::removeClient(network::IClient &c)
{
  GameServer &g = static_cast<GameServer &>(c);

  nope::log::Log(Debug) << "Removing GameServer";
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

std::vector<std::unique_ptr<GameServer>> const &
    LicenseServer::getGameServers() const
{
  return (m_gameServerList);
}

std::int32_t LicenseServer::checkActivity(fd_set &readfds, fd_set &writefds,
                                          fd_set &   exceptfds,
                                          bool const monitorLicenseServer)
{
  std::int32_t       rc = -1;
  struct timeval     tv;
  std::int32_t       maxFd;
  std::int32_t const gameSocket = m_gameServer.getSocket();

  // Check file descriptors
  do
    {
      FD_ZERO(&readfds);
      FD_ZERO(&writefds);
      FD_ZERO(&exceptfds);
      tv.tv_sec = 1;
      tv.tv_usec = 50;

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
		  nope::log::Log(Debug) << "Adding to writefds: #" << sock;
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
  return (rc);
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

  // Resize vector to max client, preallocate memory
  m_gameServerList.reserve(maxGameServer);

  nope::log::Log(Debug) << "Starting to loop";
  while (1)
    {
      fd_set readfds, writefds, exceptfds;

      // Notify each gameServer with pending requests
      std::size_t const nbTokenRequ = m_token.size();
      if (nbTokenRequ)
	{
	  nope::log::Log(Debug)
	      << "{LicenseServer} TokenRequests -> " << nbTokenRequ;
	  for (std::size_t i = 0; i < nbTokenRequ; ++i)
	    {
	      multithread::ResultGetter<TokenCom> &token = m_token.front();
	      m_token.pop();

	      // Find requested server
	      bool found = false;
	      for (std::size_t j = 0; j < m_gameServerList.size(); ++j)
		{
		  GameServer &game = *(m_gameServerList[j]);

		  if (game.isRequested(token.getData()))
		    {
		      // Found requested server, request will be treated by it.
		      nope::log::Log(Debug) << "Found requested server !";
		      game.pushRequest(token);
		      found = true;
		      break;
		    }
		}
	      if (!found)
		{
		  // Unavailable server
		  nope::log::Log(Warning) << "Couldn't find requested server";
		  token.getData().treated = 0;
		  token.notify();
		}
	    }
	}

      updateGameServerList();
      std::int32_t const rc =
          checkActivity(readfds, writefds, exceptfds, monitorLicenseServer);
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
		      nope::log::Log(Debug)
		          << "License Server disconnected. Quitting";
		      break;
		    }
		  arr[static_cast<std::size_t>(readVal)] = '\0';
                  nope::log::Log(Debug) << "std::string(arr.data())";
		  loadLicenses();
		}
	      else
		{
		  // Nothing more to read, byebye
		  nope::log::Log(Debug)
		      << "License Server disconnected. Quitting";
		  break;
		}
	    }

	  if (FD_ISSET(gameSocket, &readfds))
	    {
	      addClient();
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

		  nope::log::Log(Debug) << "Can read from socket #" << sock;
		  action = game->treatIncomingData();
		  if (action != network::IClient::ClientAction::SUCCESS)
		    {
		      removeClient(*game);
		      deleted = true;
		    }
		}
	      if (deleted == false && FD_ISSET(sock, &writefds))
		{
		  network::IClient::ClientAction action;

		  action = game->treatOutcomingData();
		  if (action != network::IClient::ClientAction::SUCCESS)
		    {
		      removeClient(*game);
		      deleted = true;
		    }
		}
	      if (deleted == false && FD_ISSET(sock, &exceptfds))
		{
		  nope::log::Log(Debug)
		      << "Something happened, disconnecting client" << sock;
		  removeClient(*game);
		  deleted = true;
		}

	      // Checks token requests
	      if (deleted == false && game->hasTimedOut())
		{
		  if (game->hasRequests())
		    {
		      if (!game->canWrite())
			{
			  // Turn to write mode
			  game->toggleWrite();
			}
		    }
		}

	      // Check if we deleted anything
	      if (!deleted)
		++iter;
	    }
	}
      else
	{
	  for (std::vector<std::unique_ptr<GameServer>>::iterator iter =
	           m_gameServerList.begin();
	       iter != m_gameServerList.end(); ++iter)
	    {
	      std::unique_ptr<GameServer> &game = *iter;

	      // Checks token requests
	      if (game->hasTimedOut())
		{
		  if (game->hasRequests())
		    {
		      if (!game->canWrite())
			{
			  // Turn to write mode
			  game->toggleWrite();
			}
		    }
		}
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

std::vector<GameServerInfo> const &LicenseServer::getGameServerList() const
{
  return (m_list);
}

std::mutex &LicenseServer::getGameServerListMut()
{
  return (m_gameServerListMut);
}

void LicenseServer::updateGameServerList()
{
  std::unique_lock<std::mutex> lock(m_gameServerListMut);
  m_list.clear();
  for (std::unique_ptr<GameServer> const &game : m_gameServerList)
    {
      m_list.push_back(GameServerInfo(game->getIp(), game->getPort(),
                                      game->getCurrentClients(),
                                      game->getMaxClients()));
    }
}
