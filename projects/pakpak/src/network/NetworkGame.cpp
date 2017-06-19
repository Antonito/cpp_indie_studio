#include "pakpak_stdafx.hpp"

namespace core
{
  NetworkGame::NetworkGame() : m_sock(nullptr)
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

  void NetworkGame::run()
  {
    nope::log::Log(Debug) << "Starting UDP exchanges";
    // TODO
  }
}
