#include "game_server_stdafx.hpp"

GameLogic::GameLogic()
{
}

GameLogic::GameLogic(GameLogic const &)
{
}

GameLogic &GameLogic::operator=(GameLogic const &other)
{
  if (this != &other)
    {
    }
  return (*this);
}

GameLogic::~GameLogic()
{
}

void GameLogic::setUp()
{
  nope::log::Log(Info) << "Setting Up GameLogic";
  // TODO
}

void GameLogic::run()
{
  nope::log::Log(Info) << "GameLogic started";
  // TODO
}

// GamePlayer infos
std::size_t GameLogic::getCurrentPlayers() const
{
  return (getCurrentHumanPlayers() + getCurrentAIs());
}

std::size_t GameLogic::getCurrentHumanPlayers() const
{
  // TODO
  return (0);
}

std::size_t GameLogic::getCurrentAIs() const
{
  // TODO
  return (0);
}

std::size_t GameLogic::getCurrentSpectator() const
{
  // TODO
  return (0);
}

void GameLogic::addHumanPlayer()
{
}

void GameLogic::addAI()
{
}

void GameLogic::addSpectator()
{
}
