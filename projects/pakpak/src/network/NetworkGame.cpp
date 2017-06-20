#include "pakpak_stdafx.hpp"

namespace core
{
  NetworkGame::NetworkGame()
      : m_sock(nullptr), m_pck(), m_pckContent(), m_running(false)
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

  void NetworkGame::run()
  {
    nope::log::Log(Debug) << "Starting UDP exchanges";
    sockaddr_in_t const *addr = &m_sock->getSockAddr();

    m_pckContent.pck.eventType = GameClientToGSEventUDP::SIMPLE_EVENT;
    m_pckContent.pck.eventData.i = 23;
    m_pck << m_pckContent;

    // TODO: rm
    for (int i = 0; i < 20; ++i)
      {
	if (writeUDP(m_pck, addr))
	  {
	    nope::log::Log(Debug) << "Send UDP packet";
	  }
      }

    // TODO
    m_running = true;
    while (m_running)
      {
	// Get Game events
	// Send game events to server
	// Read Server events
	// Send server events to game
      }
  }
}
