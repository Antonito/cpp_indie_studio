#include "GameClient.hpp"

GameClient::GameClient()
{
}

GameClient::~GameClient()
{
}

GameClient::GameClient(GameClient const &)
{
}

GameClient &GameClient::operator=(GameClient const &other)
{
  if (&other != this)
    {
    }
  return (*this);
}

bool GameClient::disconnect()
{
  // TODO
  return (true);
}

network::IClient::ClientAction GameClient::write(IPacket const &)
{
  // TODO
  return (network::IClient::ClientAction::FAILURE);
}

network::IClient::ClientAction GameClient::read(IPacket &)
{
  // TODO
  return (network::IClient::ClientAction::FAILURE);
}

bool GameClient::hasTimedOut() const
{
  // TODO
  return (false);
}
