#include "connect_manager_stdafx.hpp"

constexpr std::uint32_t GameClientServer::maxGameClients;

GameClientServer::GameClientServer(std::uint16_t const port)
    : m_sock(port, GameClientServer::maxGameClients,
             network::ASocket::BLOCKING),
      m_thread()
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

void GameClientServer::_loop()
{
  // TODO: Code
  while (1)
    {
      break;
    }
}
