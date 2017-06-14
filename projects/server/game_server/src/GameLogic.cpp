#include "game_server_stdafx.hpp"

GameLogic::GameLogic()
    : m_running(false), m_maxPlayers(), m_currentHumanPlayers(),
      m_currentAIs(), m_currentSpectators(), m_maps(), m_currentMap(),
      m_prevState(GameState::LOADING), m_state(GameState::LOADING)
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
  // TODO
  // Get config, load maps
  nope::log::Log(Info) << "Setting Up GameLogic";

  m_maxPlayers = static_cast<std::size_t>(
      Config::getInstance().getGameServerMaxClients());
  std::vector<MapConfig> const &mapConfig =
      Config::getInstance().getMapConfig();
  if (mapConfig.size() < 1)
    {
      nope::log::Log(Error) << "Incorrect number of maps [GameLogic]";
      throw std::exception(); // TODO
    }
  m_maps = mapConfig;
  m_currentMap = m_maps.begin();
  m_running = true;
}

void GameLogic::loadingState()
{
  assert(m_state == GameState::LOADING);
  if (m_prevState == GameState::PLAYING)
    {
      // Stop previous game
    }

  // Check if any human players (players or spectators)
  if (getCurrentPlayers() > 0)
    {
      // Loop over clients
      // Wait for all of their signal
    }
  setState(GameState::PLAYING);
}

void GameLogic::playingState()
{
  assert(m_state == GameState::PLAYING);
  // Get packets
  // GameLogic process
  // Send packets
}

void GameLogic::run()
{
  // Configure game logic
  setUp();
  nope::log::Log(Info) << "GameLogic started";

  // Loop
  while (m_running)
    {
      if (m_state == GameState::LOADING)
	{
	  loadingState();
	}
      else
	{
	  playingState();
	}
    }
}

void GameLogic::nextMap()
{
  // Play next map
  nope::log::Log(Debug) << "Changing map";
  ++m_currentMap;
  if (m_currentMap == m_maps.end())
    {
      m_currentMap = m_maps.begin();
    }
  setState(GameState::LOADING);
}

// GamePlayer infos
std::size_t GameLogic::getCurrentPlayers() const
{
  return (getCurrentHumanPlayers() + getCurrentSpectator());
}

std::size_t GameLogic::getCurrentHumanPlayers() const
{
  return (m_currentHumanPlayers);
}

std::size_t GameLogic::getCurrentAIs() const
{
  return (m_currentAIs);
}

std::size_t GameLogic::getCurrentSpectator() const
{
  return (m_currentSpectators);
}

GameLogic::map_t const &GameLogic::getCurrentMap() const
{
  return (*m_currentMap);
}

// Players
void GameLogic::addHumanPlayer()
{
  // TODO
}

void GameLogic::addAI()
{
  // TODO
}

void GameLogic::deleteAI()
{
  // TODO
}

void GameLogic::addSpectator()
{
  // TODO
}

void GameLogic::loadMap()
{
  // TODO
}

void GameLogic::setState(GameState const state)
{
  m_prevState = m_state;
  m_state = state;
}
