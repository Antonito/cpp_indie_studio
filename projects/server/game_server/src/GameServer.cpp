#include "game_server_stdafx.hpp"

GameServer::GameServer(std::string const & connectManagerIp,
                       std::uint16_t const cmPort, std::uint16_t const gsPort,
                       std::int32_t const maxClients)
    : m_connectManagerPort(cmPort), m_gameServerPort(gsPort),
      m_maxClients(maxClients),
      m_connectManagerSock(m_connectManagerPort, connectManagerIp, true,
                           network::ASocket::SocketType::BLOCKING)
{
}

GameServer::~GameServer()
{
}

bool GameServer::run()
{
  nope::log::Log(Debug) << "Running Game Server";
  if (m_connectManagerSock.openConnection())
    {
      nope::log::Log(Debug) << "Connected to ConnectManager";
      return (true);
    }
  return (false);
}

void GameServer::stop()
{
}

bool GameServer::addClient()
{
  return (true);
}

bool GameServer::removeClient(network::IClient &)
{
  return (true);
}
