#include "game_server_stdafx.hpp"

network::IClient::ClientAction GameServer::writeUDP(IPacket const &      pck,
                                                    sockaddr_in_t const *addr)
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::SUCCESS;
  std::size_t const              sizeToWrite = pck.getSize();
  std::uint8_t const *           data = pck.getData();

  if (m_gameSockUDP.send(data, sizeToWrite,
                         reinterpret_cast<sockaddr_t const *>(addr),
                         sizeof(*addr)) == false)
    {
      nope::log::Log(Debug) << "Failed to write data [GameServerUDP]";
      ret = network::IClient::ClientAction::FAILURE;
    }
  return (ret);
}

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
      // TODO: Use memory pool
      std::size_t const pckSize = packetSize::GameClientToGSPacketUDPSize;
      std::unique_ptr<uint8_t[]> buff =
          std::make_unique<std::uint8_t[]>(pckSize);
      sockaddr_in_t cliAddr;
      socklen_t     len = sizeof(cliAddr);

      if (m_gameSockUDP.rec(buff.get(), pckSize,
                            reinterpret_cast<sockaddr_t *>(&cliAddr), &len))
	{
	  nope::log::Log(Debug) << "{GameServerUDP} Received packet ["
	                        << inet_ntoa(cliAddr.sin_addr) << ":"
	                        << ntohs(cliAddr.sin_port) << "]";
	  m_pckUDP.setData(pckSize, std::move(buff));

	  // Check if client exist
	  std::vector<UDPClient>::iterator ite =
	      std::find(m_clientUDP.begin(), m_clientUDP.end(), cliAddr);
	  if (ite == m_clientUDP.end())
	    {
	      GameClientToGSPacketUDP tmp;

	      m_pckUDP >> tmp;
	      // Client is new, add it to vector
	      m_clientUDP.push_back(
	          UDPClient(cliAddr, m_gameSockUDP, tmp.pck.id));
	      nope::log::Log(Info)
	          << "Added new client to server. [GameServerUDP]";
	      ite = m_clientUDP.end() - 1; // Get iterator on added element
	    }

	  // 'ite' is now the current client
	  (*ite) << m_pckUDP;
	  ite->updateAction(); // Update timeout
	}
      else
	{
	  nope::log::Log(Error)
	      << "Cannot read [GameServerUDP] : " << std::strerror(errno);
	}
    }
  // Loop over all clients and broadcast
  return (0);
}

void GameServer::deleteUDPClient(UDPClient &cli)
{
  nope::log::Log(Info) << "Removing UDP Client [GameServerUDP]";
  cli.disconnect();

  // Remove asked element
  m_clientUDP.erase(
      std::remove_if(m_clientUDP.begin(), m_clientUDP.end(),
                     [&](UDPClient const &o) { return (o == cli); }),
      m_clientUDP.end());
}

void GameServer::updateUDPTick()
{
  m_tickUDP = std::chrono::system_clock::now();
}

void GameServer::gameServerUDP()
{
  std::int32_t const sock = m_gameSockUDP.getSocket();

  nope::log::Log(Info) << "Game Server UDP started [GameServerUDP]";
  assert(sock >= 0);
  updateUDPTick();
  while (1)
    {
      std::chrono::system_clock::time_point const now =
          std::chrono::system_clock::now();
      // Check activity
      fd_set             readfds, writefds, exceptfds;
      std::int32_t const rc =
          gameServerUDPActivity(sock, readfds, writefds, exceptfds);

      if (rc < 0)
	{
	  // There was an error
	  nope::log::Log(Error) << "select() failed [GameServerUDP]";
	  break;
	}
      else if (rc > 0)
	{
	  // Treat I/O
	  gameServerUDPIO(sock, readfds, writefds, exceptfds);
	}

      // Check server's tick
      if (std::chrono::duration_cast<std::chrono::milliseconds>(now -
                                                                m_tickUDP)
              .count() >= 17 * 2)
	{
	  // Loop over each client to send its packet
	  for (std::vector<UDPClient>::iterator ite = m_clientUDP.begin();
	       ite != m_clientUDP.end();)
	    {
	      bool       deleted = false;
	      UDPClient &cli = *ite;

	      if (cli.hasTimedOut())
		{
		  deleteUDPClient(cli);
		  deleted = true;
		}
	      else if (!deleted)
		{
		  // Serialize current packet
		  m_pckUDP << cli.getData();
		  // Loop over all clients
		  for (UDPClient &_cli : m_clientUDP)
		    {
		      // Send packet to client
		      nope::log::Log(Debug)
		          << "Sending packet from client " << ite->getId()
		          << " to client " << _cli.getId();
		      _cli.write(m_pckUDP);
		    }
		}
	      if (!deleted)
		{
		  ++ite;
		}
	    }
	}
    }
}
