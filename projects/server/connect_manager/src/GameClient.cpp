#include "GameClient.hpp"

GameClient::GameClient(sock_t const fd)
    : m_sock(fd), m_write(false), __padding()
{
}

GameClient::~GameClient()
{
}

bool GameClient::disconnect()
{
  // TODO
  return (false);
}

network::IClient::ClientAction GameClient::write(IPacket const &)
{
  // TODO
  return (network::IClient::ClientAction::DISCONNECT);
}

network::IClient::ClientAction GameClient::read(IPacket &)
{
  // TODO
  return (network::IClient::ClientAction::DISCONNECT);
}

bool GameClient::hasTimedOut() const
{
  // TODO
  return (false);
}

std::int32_t GameClient::getSocket() const
{
  return (m_sock.getSocket());
}

bool GameClient::canWrite() const
{
  return (m_write);
}

void GameClient::toggleWrite()
{
  m_write = !m_write;
}
