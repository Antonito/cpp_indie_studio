#include "connect_manager_stdafx.hpp"

GameServer::GameServer(sock_t socket, sockaddr_in_t const &in)
    : m_sock(socket), m_in(in), m_write(false), m_state(State::CONNECTED)
{
  std::array<char, INET6_ADDRSTRLEN> clntName;

  if (::getnameinfo(reinterpret_cast<sockaddr_t *>(&m_in), sizeof(m_in),
                    clntName.data(), sizeof(clntName), nullptr, 0,
                    NI_NUMERICHOST | NI_NUMERICSERV) == 0)
    {
      nope::log::Log(Info) << "Client joined " << std::string(clntName.data())
                           << std::endl;
    }
}

GameServer::GameServer(GameServer &&other)
    : m_sock(std::move(other.m_sock)), m_in(std::move(other.m_in)),
      m_write(other.m_write), m_state(other.m_state)
{
}

sock_t GameServer::getSocket() const
{
  return (m_sock.getSocket());
}

bool GameServer::canWrite() const
{
  return (m_write);
}

bool GameServer::disconnect()
{
  nope::log::Log(Debug) << "Client disconnected #" << getSocket();
  m_sock.closeConnection();
  return (true);
}

network::IClient::ClientAction GameServer::write()
{
  return (network::IClient::ClientAction::DISCONNECT);
}

network::IClient::ClientAction GameServer::read()
{
  return (network::IClient::ClientAction::DISCONNECT);
}

bool GameServer::hasTimedOut() const
{
  return (false);
}

void GameServer::toggleWrite()
{
  m_write = !m_write;
}

bool GameServer::operator==(GameServer const &other) const
{
  if (this != &other)
    {
      return (m_sock == other.m_sock);
    }
  return (true);
}

network::IClient::ClientAction GameServer::treatIncomingData()
{
  // TODO: State machine
  switch (m_state)
    {
    case State::CONNECTED:
      break;
    case State::SETTING:
      break;
    case State::AUTHENTICATED:
      nope::log::Log(Info) << "GameServer " << getSocket() << " authenticated."
                           << std::endl; // TODO: Put here or output ?
      break;
    }
}

network::IClient::ClientAction GameServer::treatOutcomingData()
{
  // TODO: State machine
  switch (m_state)
    {
    case State::CONNECTED:
      break;
    case State::SETTING:
      break;
    case State::AUTHENTICATED:
      break;
    }
}
