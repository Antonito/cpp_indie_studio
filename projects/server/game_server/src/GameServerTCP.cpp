#include "game_server_stdafx.hpp"

bool GameServer::addClient()
{
  std::int32_t  rc = 0;
  sockaddr_in_t in = {};
  sock_t const  sock = m_gameSock.getSocket();

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
      m_clientList.push_back(
          std::make_unique<GameClient>(rc, m_tokenList, m_clientList.size()));
      nope::log::Log(Debug)
          << "Added client FD #" << m_clientList.back()->getSocket();
      nope::log::Log(Info) << "New player connected #"
                           << m_clientList.back()->getId();
      ++m_curClients;
      nope::log::Log(Debug) << "There are now " << m_curClients << " clients.";
      return (true);
    }
  return (false);
}

bool GameServer::removeClient(network::IClient &c)
{
  GameClient &g = static_cast<GameClient &>(c);

  nope::log::Log(Debug) << "Removing GameClient";
  nope::log::Log(Info) << "Player disconnected #" << g.getId();
  g.disconnect();

  // Remove asked element
  m_clientList.erase(std::remove_if(m_clientList.begin(), m_clientList.end(),
                                    [&](std::unique_ptr<GameClient> const &o) {
                                      return (*o == g);
                                    }),
                     m_clientList.end());
  --m_curClients;
  nope::log::Log(Debug) << "There are now " << m_curClients << " clients.";
  return (true);
}

std::int32_t GameServer::gameServerTCPActivity(std::int32_t const sock,
                                               fd_set &           readfds,
                                               fd_set &           writefds,
                                               fd_set &           exceptfds)
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

      // Loop over all the clients
      for (std::vector<std::unique_ptr<GameClient>>::const_iterator ite =
               m_clientList.begin();
           ite != m_clientList.end(); ++ite)
	{
	  sock_t const curSock = (*ite)->getSocket();

	  if (curSock > maxSock)
	    {
	      maxSock = curSock;
	    }
	  FD_SET(curSock, &readfds);
	  if ((*ite)->canWrite())
	    {
	      FD_SET(curSock, &writefds);
	    }
	}

      exceptfds = readfds;
      rc = select(maxSock + 1, &readfds, &writefds, &exceptfds, &tv);
    }
  while (rc == -1 && errno == EINTR);
  return (rc);
}

std::int32_t GameServer::gameServerTCPIO(std::int32_t const sock,
                                         fd_set &readfds, fd_set &writefds,
                                         fd_set &exceptfds)
{
  if (FD_ISSET(sock, &readfds))
    {
      addClient();
    }

  // Loop over connected clients
  for (std::vector<std::unique_ptr<GameClient>>::iterator ite =
           m_clientList.begin();
       ite != m_clientList.end();)
    {
      bool         deleted = false;
      GameClient & game = **ite;
      sock_t const gameSocket = game.getSocket();

      if (FD_ISSET(gameSocket, &readfds))
	{
	  // Handle input
	  network::IClient::ClientAction action;

	  nope::log::Log(Debug) << "Can read from socket #" << gameSocket;
	  action = game.treatIncomingData();
	  if (action != network::IClient::ClientAction::SUCCESS)
	    {
	      removeClient(game);
	      deleted = true;
	    }
	}
      if (deleted == false && FD_ISSET(gameSocket, &writefds))
	{
	  // Handle output
	  network::IClient::ClientAction action;

	  nope::log::Log(Debug) << "Can write from socket #" << gameSocket;
	  action = game.treatOutgoingData();
	  if (action != network::IClient::ClientAction::SUCCESS)
	    {
	      removeClient(game);
	      deleted = true;
	    }
	}
      if (deleted == false && FD_ISSET(gameSocket, &exceptfds))
	{
	  // Handle exception
	  removeClient(game);
	  deleted = true;
	}

      // Check if we deleted anything
      if (!deleted)
	{
	  ++ite;
	}
    }
  return (0);
}

void GameServer::gameServerTCP()
{
  std::int32_t const sock = m_gameSock.getSocket();

  assert(sock >= 0);
  while (1)
    {
      // Check activity
      fd_set             readfds, writefds, exceptfds;
      std::int32_t const rc =
          gameServerTCPActivity(sock, readfds, writefds, exceptfds);

      if (rc < 0)
	{
	  // There was an error
	  nope::log::Log(Error) << "select() failed [TCP]";
	  break;
	}
      else if (rc > 0)
	{
	  // Treat I/O
	  gameServerTCPIO(sock, readfds, writefds, exceptfds);
	}
    }
}
