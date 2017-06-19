#include "game_server_stdafx.hpp"

std::int32_t GameServer::gameServerUDPActivity(std::int32_t const sock,
                                               fd_set &readfds, fd_set &,
                                               fd_set &)
{
  std::int32_t rc = 0;
  do
    {
      struct timeval tv;
      std::int32_t   maxSock = sock;

      FD_ZERO(&readfds);
      tv.tv_sec = 5;
      tv.tv_usec = 0;

      FD_SET(sock, &readfds);

      rc = select(maxSock + 1, &readfds, nullptr, nullptr, &tv);
    }
  while (rc == -1 && errno == EINTR);
  return (rc);
}

std::int32_t GameServer::gameServerUDPIO(std::int32_t const sock,
                                         fd_set &readfds, fd_set &, fd_set &)
{
  if (FD_ISSET(sock, &readfds))
    {
      sockaddr_in_t addr;
      socklen_t     len;

      m_gameSockUDP.rec(nullptr, 0, reinterpret_cast<sockaddr_t *>(&addr),
                        &len);
      // TODO: Read from client

      // Check if client exist
    }
  return (0);
}

void GameServer::gameServerUDP()
{
  std::int32_t const sock = m_gameSockUDP.getSocket();

  nope::log::Log(Info) << "Game Server UDP started";
  assert(sock >= 0);
  while (1)
    {
      // Check activity
      fd_set             readfds, writefds, exceptfds;
      std::int32_t const rc =
          gameServerUDPActivity(sock, readfds, writefds, exceptfds);

      if (rc < 0)
	{
	  // There was an error
	  nope::log::Log(Error) << "select() failed [TCP]";
	  break;
	}
      else if (rc > 0)
	{
	  // Treat I/O
	  gameServerUDPIO(sock, readfds, writefds, exceptfds);
	}
    }
}
