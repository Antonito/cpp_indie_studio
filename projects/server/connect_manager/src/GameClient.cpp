#include "GameClient.hpp"

GameClient::GameClient(sock_t const fd)
    : m_sock(fd), m_write(false), m_state(State::CONNECTED)
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

bool GameClient::operator==(GameClient const &other) const
{
  if (this != &other)
    {
      return (m_sock == other.m_sock);
    }
  return (true);
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

network::IClient::ClientAction GameClient::treatIncomingData()
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;

  switch (m_state)
    {
    case State::CONNECTED:
      break;
    case State::AUTHENTICATED:
      break;
    }
  if (ret == network::IClient::ClientAction::SUCCESS)
    {
      toggleWrite();
    }
  return (ret);
}

network::IClient::ClientAction GameClient::treatOutcomingData()
{
  network::IClient::ClientAction ret = network::IClient::ClientAction::FAILURE;

  switch (m_state)
    {
    case State::CONNECTED:
      break;
    case State::AUTHENTICATED:
      nope::log::Log(Info) << "GameClient " << getSocket()
                           << " authenticated."; // TODO: Put here or output ?
      break;
    }
  if (ret == network::IClient::ClientAction::SUCCESS)
    {
      toggleWrite();
    }
  return (ret);
}
