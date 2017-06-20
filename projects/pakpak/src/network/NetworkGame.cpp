#include "pakpak_stdafx.hpp"

namespace core
{
  NetworkGame::NetworkGame()
      : m_sock(nullptr), m_pck(), m_pckContent(), m_running(false),
        m_gamePckIn(), m_gamePckOut()
  {
  }

  NetworkGame::~NetworkGame()
  {
  }

  void NetworkGame::init(std::uint16_t const port, std::string const &addr)
  {
    nope::log::Log(Debug) << "Initializing UDP connection.";
    m_sock = std::make_shared<network::UDPSocket>(
        port, addr, true, network::ASocket::SocketType::BLOCKING);
    if (!m_sock->openConnection())
      {
	nope::log::Log(Error) << "Cannot create UDP connection.";
	throw NetworkConnectionError("Cannot create UDP connection.");
      }
  }

  network::IClient::ClientAction
      NetworkGame::writeUDP(IPacket const &pck, sockaddr_in_t const *addr)
  {
    network::IClient::ClientAction ret =
        network::IClient::ClientAction::SUCCESS;
    std::size_t const   sizeToWrite = pck.getSize();
    std::uint8_t const *data = pck.getData();
    socklen_t const     addrlen = (addr) ? sizeof(*addr) : 0;

    if (m_sock->send(data, sizeToWrite,
                     reinterpret_cast<sockaddr_t const *>(addr),
                     addrlen) == false)
      {
	nope::log::Log(Debug) << "Failed to write data [NetworkGame]";
	nope::log::Log(Error) << std::strerror(errno);
	ret = network::IClient::ClientAction::FAILURE;
      }
    return (ret);
  }

  void NetworkGame::stop()
  {
    m_running = false;
  }

  void NetworkGame::sendPacket(GameClientToGSPacketUDP const &pck)
  {
    m_gamePckIn.push(pck);
  }

  std::vector<GameClientToGSPacketUDP> NetworkGame::getPacket()
  {
    std::vector<GameClientToGSPacketUDP> events;

    // Poll out events
    while (!m_gamePckOut.empty())
      {
	events.push_back(m_gamePckOut.front());
	m_gamePckOut.pop();
      }
    return (events);
  }

  void NetworkGame::run()
  {
    nope::log::Log(Debug) << "Starting UDP exchanges";
    sockaddr_in_t const *addr = &m_sock->getSockAddr();

    m_running = true;
    std::vector<GameClientToGSPacketUDP> gameEvents;
    while (m_running)
      {
	// Clear datas
	gameEvents.clear();

	// Monitoring socket
	fd_set       readfds, writefds;
	sock_t const sock = m_sock->getSocket();
	std::int32_t ret = 0;

	do
	  {
	    struct timeval tv;

	    tv.tv_sec = 5;
	    tv.tv_usec = 0;
	    FD_ZERO(&readfds);
	    FD_ZERO(&writefds);

	    FD_SET(sock, &readfds);
	    if (!m_gamePckIn.empty())
	      {
		FD_SET(sock, &writefds);
	      }

	    ret = select(sock + 1, &readfds, &writefds, nullptr, &tv);
	  }
	while (ret == -1 && errno == EINTR);

	if (ret == -1)
	  {
	    nope::log::Log(Error) << "Select failed " << std::strerror(errno)
	                          << " [NetworkGame]";
	    break;
	  }
	else if (ret > 0)
	  {
	    // Treat inputs
	    if (FD_ISSET(sock, &readfds))
	      {
		std::unique_ptr<std::uint8_t[]> buff =
		    std::make_unique<std::uint8_t[]>(
		        packetSize::GameClientToGSPacketUDPSize);

		Packet<GameClientToGSPacketUDP> pck;
		GameClientToGSPacketUDP         packetUDP;

		socklen_t     len = sizeof(*addr);
		sockaddr_in_t addrCpy;

		std::memcpy(&addrCpy, addr, sizeof(*addr));
		if (m_sock->rec(
		        buff.get(), packetSize::GameClientToGSPacketUDPSize,
		        reinterpret_cast<sockaddr_t *>(&addrCpy), &len))
		  {
		    nope::log::Log(Debug) << "Received packet {UDP}";
		    pck.setData(packetSize::GameClientToGSPacketUDPSize,
		                std::move(buff));
		    pck >> packetUDP;
		    m_gamePckOut.push(packetUDP);
		  }
	      }

	    // Treat output
	    if (FD_ISSET(sock, &writefds))
	      {
		// Get Game events
		while (!m_gamePckIn.empty())
		  {
		    gameEvents.push_back(m_gamePckIn.front());
		    m_gamePckIn.pop();
		  }

		// Send game events to server
		for (GameClientToGSPacketUDP const &ev : gameEvents)
		  {
		    m_pck << ev;
		    if (writeUDP(m_pck, addr) !=
		        network::IClient::ClientAction::SUCCESS)
		      {
			nope::log::Log(Warning) << "Couldn't send UDP packet";
		      }
		  }
	      }
	  }
      }
  }
}
