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

	// Read Server events
	std::vector<GameClientToGSPacketUDP> serverEvents;
	GameClientToGSPacketUDP              packetUDP;
	socklen_t                            len = sizeof(*addr);
	sockaddr_in_t                        addrCpy;
	std::uint16_t                        playerCount = 0;
	std::uint16_t                        cur = 0;

	std::memcpy(&addrCpy, addr, sizeof(*addr));

        //TODO Antoine :: non-blocking read
        #if 0
	do
	  {
	    if (!m_sock->rec(&packetUDP, sizeof(packetUDP),
			     reinterpret_cast<sockaddr_t *>(&addrCpy), &len))
	      {
		nope::log::Log(Debug)
		    << "Error occured while receiving packet : " << cur << ".";
		break;
	      }
	    if (!cur)
	      {
		playerCount = packetUDP.pck.playerCount;
                nope::log::Log(Debug)
                    << "Total player count :\n\t" << playerCount << ".";
	      }
	    serverEvents.push_back(packetUDP);
	    ++cur;
	  }
	while (cur < playerCount);
        #endif

	// Send server events to game
	while (!serverEvents.empty())
	  {
	    m_gamePckOut.push(std::move(serverEvents.back()));
	    serverEvents.pop_back();
	  }
      }
  }
}
