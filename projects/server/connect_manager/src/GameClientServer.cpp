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
  // TODO: Code
  return (true);
}

bool GameClientServer::removeClient(network::IClient &)
{
  // TODO: Code
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
		  // TODO: Check input
		}
	      if (!deleted && FD_ISSET(sock, &writefds))
		{
		  // TODO: Ouput
		}
	      if (!deleted && FD_ISSET(sock, &exceptfds))
		{
		  // TODO: Except
		}
	      if (!deleted)
		{
		  ++iter;
		}
	    }
	}
    }
}
