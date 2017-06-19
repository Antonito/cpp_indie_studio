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
      nope::log::Log(Debug) << "Failed to write data [GameClient]";
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
      nope::log::Log(Debug) << "There's data to read [UDP]";
      // TODO: Use memory pool
      std::size_t const pckSize = packetSize::GameClientToGSPacketUDPSize;
      std::unique_ptr<uint8_t[]> buff =
          std::make_unique<std::uint8_t[]>(pckSize);
      sockaddr_in_t addr;
      socklen_t     len;

      if (m_gameSockUDP.rec(buff.get(), pckSize,
                            reinterpret_cast<sockaddr_t *>(&addr), &len))
	{
	  nope::log::Log(Debug)
	      << "**UDP** Received packet [" << inet_ntoa(addr.sin_addr) << ":"
	      << ntohs(addr.sin_port) << "]";
	  m_pckUDP.setData(pckSize, std::move(buff));
	  m_pckUDP >> m_repUDP;

	  // Check if client exist
	}
      else
	{
	  nope::log::Log(Error)
	      << "Cannot read [UDP] : " << std::strerror(errno);
	}
    }
  // Loop over all clients and broadcast
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
	  nope::log::Log(Error) << "select() failed [UDP]";
	  break;
	}
      else if (rc > 0)
	{
	  // Treat I/O
	  nope::log::Log(Debug) << "Treating I/O [UDP]";
	  gameServerUDPIO(sock, readfds, writefds, exceptfds);
	}
    }
}
