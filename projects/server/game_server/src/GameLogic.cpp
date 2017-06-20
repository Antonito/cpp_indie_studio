#include "game_server_stdafx.hpp"

GameLogic::GameLogic()
    : m_running(false), m_playing(false), m_maxPlayers(),
      m_currentHumanPlayers(), m_currentAIs(), m_currentSpectators(), m_maps(),
      m_currentMap(), m_nextMap(), m_prevState(GameState::LOADING),
      m_state(GameState::LOADING), m_humans(), m_spectators(), m_ai()
{
}

GameLogic::~GameLogic()
{
}

void GameLogic::setUp()
{
  // Get config, load maps
  nope::log::Log(Info) << "Setting Up GameLogic";

  m_maxPlayers = static_cast<std::size_t>(
      Config::getInstance().getGameServerMaxClients());

  // Preallocate memory
  nope::log::Log(Debug) << "Pre-allocating memory";
  m_humans.reserve(m_maxPlayers);
  m_spectators.reserve(m_maxPlayers);
  m_ai.reserve(m_maxPlayers);

  // Load maps TODO
  nope::log::Log(Debug) << "Loading map informations";
  std::vector<MapConfig> const &mapConfig =
      Config::getInstance().getMapConfig();
  if (mapConfig.size() < 1)
    {
      nope::log::Log(Error) << "Incorrect number of maps [GameLogic]";
      throw MapError("Incorrect number of maps [GameLogic]");
    }
  m_maps = mapConfig;
  m_currentMap = m_maps.begin();
  m_running = true;
}

void GameLogic::stopGame()
{
  // TODO
  // Stop previous game -> m_currentMap
}

void GameLogic::syncClients()
{
  // TODO
  // Loop over clients
  // Wait for all of their signal
}

void GameLogic::loadingState()
{
  nope::log::Log(Debug) << "GameLogic in Loading state";
  assert(m_state == GameState::LOADING);
  if (m_prevState == GameState::PLAYING)
    {
      stopGame();
    }

  // Check if any human players (players or spectators)
  if (getCurrentPlayers() > 0)
    {
      // Move spectators to players
      assert(m_currentSpectators == m_spectators.size());
      for (std::size_t i = 0; i < m_currentSpectators; ++i)
	{
	  m_humans.push_back(std::move(m_spectators.back()));
	  m_spectators.pop_back();
	}
      updatePlayersCount();
      syncClients();
    }
  m_currentMap = m_nextMap;
  setState(GameState::PLAYING);
}

void GameLogic::playingState()
{
  nope::log::Log(Debug) << "GameLogic in Playing state";
  assert(m_state == GameState::PLAYING);
  m_playing = true;
  while (m_playing)
    {
      //   Get packets
      //   GameLogic process
      //   Send packets
      sleep(1); // TODO: rm
    }

  // Load next game
  nextMap();
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
  nope::log::Log(Info) << "GameLogic over.";
}

void GameLogic::requestNextGame()
{
  // Request next game
  nope::log::Log(Debug) << "Requesting a map change";
}

void GameLogic::nextMap()
{
  // Play next map
  nope::log::Log(Debug) << "Changing map";
  m_nextMap = m_currentMap;
  ++m_nextMap;
  if (m_nextMap == m_maps.end())
    {
      m_nextMap = m_maps.begin();
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

void GameLogic::removeHumanPlayer()
{
  // TODO
}

void GameLogic::addAI()
{
  // TODO
}

void GameLogic::removeAI()
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

void GameLogic::updatePlayersCount()
{
  m_currentHumanPlayers = m_humans.size();
  m_currentAIs = m_ai.size();
  m_currentSpectators = m_spectators.size();
  assert(m_currentHumanPlayers + m_currentAIs <= m_maxPlayers);
  assert(m_currentHumanPlayers + m_currentSpectators <= m_maxPlayers);
}
