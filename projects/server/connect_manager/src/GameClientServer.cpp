#include "connect_manager_stdafx.hpp"

constexpr std::uint32_t GameClientServer::maxGameClients;

GameClientServer::GameClientServer(std::uint16_t const port)
    : m_sock(port, GameClientServer::maxGameClients,
             network::ASocket::BLOCKING),
      m_thread(), m_gameClient()
{
}

GameClientServer::~GameClientServer()
{
}

bool GameClientServer::run()
{
  nope::log::Log(Debug) << "Running gameClient server";
  if (m_sock.openConnection())
    {
      nope::log::Log(Debug) << "Connection opened";
      m_thread = std::thread([&]() { this->_loop(); });
      return (true);
    }
  nope::log::Log(Error) << "Cannot open connection";
  return (false);
}

void GameClientServer::stop()
{
  if (m_thread.joinable())
    {
      m_thread.join();
    }
}

bool GameClientServer::addClient()
{
  // Accept new client
  std::int32_t  rc = 0;
  sockaddr_in_t in = {};
  sock_t const  sock = m_sock.getSocket();

  nope::log::Log(Debug) << "There's client to accept on socket #" << sock;
  do
    {
      socklen_t len = sizeof(in);
      rc = ::accept(sock, reinterpret_cast<sockaddr_t *>(&in), &len);
    }
  while (rc == -1 && errno == EINTR);

  // Check if the socket is valid
  if (rc > 0)
    {
      m_gameClient.push_back(
          std::make_unique<GameClient>(rc)); // TODO: Use in ?
      nope::log::Log(Debug) << "Added client FD #"
                            << m_gameClient.back()->getSocket();
      return (true);
    }
  return (false);
}

bool GameClientServer::removeClient(network::IClient &c)
{
  GameClient &g = static_cast<GameClient &>(c);

  nope::log::Log(Debug) << "Removing GameClient";
  g.disconnect();
  // Remove asked element
  m_gameClient.erase(std::remove_if(m_gameClient.begin(), m_gameClient.end(),
                                    [&](std::unique_ptr<GameClient> const &o) {
                                      return (*o == g);
                                    }),
                     m_gameClient.end());
  return (true);
}

std::int32_t GameClientServer::checkActivity(fd_set &readfds, fd_set &writefds,
                                             fd_set &exceptfds)
{
  std::int32_t   rc = -1;
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

      // Add Game Server's socket
      maxFd = m_sock.getSocket();
      FD_SET(maxFd, &readfds);

      // Add every gameClient
      for (std::unique_ptr<GameClient> const &game : m_gameClient)
	{
	  std::int32_t const sock = game->getSocket();

	  FD_SET(sock, &readfds);
	  FD_SET(sock, &exceptfds);
	  if (game->canWrite())
	    {
	      FD_SET(sock, &writefds);
	    }
	  if (sock > maxFd)
	    {
	      maxFd = sock;
	    }
	}

      // Loop over gameServers
      rc = select(maxFd + 1, &readfds, &writefds, &exceptfds, &tv);
    }
  while (rc == -1 && errno == EINTR);
  return (rc);
}

void GameClientServer::_loop()
{
  while (1)
    {
      fd_set readfds, writefds, exceptfds;

      std::int32_t const rc = checkActivity(readfds, writefds, exceptfds);
      if (rc < 0)
	{
	  // There was an error
	  nope::log::Log(Error) << "select() failed";
	  break;
	}
      else if (rc > 0)
	{
	  // Handle IO
	  if (FD_ISSET(m_sock.getSocket(), &readfds))
	    {
	      addClient();
	    }

	  // Loop over all clients
	  for (std::vector<std::unique_ptr<GameClient>>::iterator iter =
	           m_gameClient.begin();
	       iter != m_gameClient.end();)
	    {
	      bool                         deleted = false;
	      std::unique_ptr<GameClient> &client = *iter;
	      std::int32_t                 sock = client->getSocket();

	      if (FD_ISSET(sock, &readfds))
		{
		  network::IClient::ClientAction ret;

		  ret = client->treatIncomingData();
		  if (ret == network::IClient::ClientAction::DISCONNECT)
		    {
		      removeClient(*client);
		      deleted = true;
		    }
		}
	      if (!deleted && FD_ISSET(sock, &writefds))
		{
		  network::IClient::ClientAction ret;

		  ret = client->treatOutcomingData();
		  if (ret == network::IClient::ClientAction::DISCONNECT)
		    {
		      removeClient(*client);
		      deleted = true;
		    }
		}
	      if (!deleted && FD_ISSET(sock, &exceptfds))
		{
		  nope::log::Log(Debug)
		      << "Something happened, disconnecting client" << sock;
		  removeClient(*client);
		  deleted = true;
		}
	      if (!deleted)
		{
		  ++iter;
		}
	    }
	}
    }
}
