#include "game_server_stdafx.hpp"

bool GameServer::addClient()
{
  return (true);
}

bool GameServer::removeClient(network::IClient &)
{
  return (true);
}

std::int32_t GameServer::gameServerTCPActivity(std::int32_t const sock,
                                               fd_set &           readfds,
                                               fd_set &           writefds,
                                               fd_set &           exceptfds,
                                               bool               canWrite)
{
  std::int32_t rc = 0;
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
  return (rc);
}

std::int32_t GameServer::gameServerTCPIO(std::int32_t const sock,
                                         fd_set &readfds, fd_set &writefds,
                                         fd_set &exceptfds, bool canWrite)
{
  if (FD_ISSET(sock, &readfds))
    {
      addClient();
    }

  // Loop over connected clients
  for (std::vector<GameClient>::iterator ite = m_clientList.begin();
       ite != m_clientList.end(); ++ite)
    {
      GameClient &game = *ite;
    }
  return (0);
}

void GameServer::gameServerTCP()
{
  std::int32_t const sock = m_gameSock.getSocket();
  bool               canWrite = false;

  assert(sock >= 0);
  while (1)
    {
      // Check activity
      fd_set             readfds, writefds, exceptfds;
      std::int32_t const rc =
          gameServerTCPActivity(sock, readfds, writefds, exceptfds, canWrite);

      if (rc < 0)
	{
	  // There was an error
	  nope::log::Log(Error) << "select() failed [TCP]";
	  break;
	}
      else if (rc > 0)
	{
	  // Treat I/O
	  if (gameServerTCPIO(sock, readfds, writefds, exceptfds, canWrite))
	    {
	      break;
	    }
	}
    }
}
