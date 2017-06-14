#ifndef GAME_LOGIC_HPP_
#define GAME_LOGIC_HPP_

#include <cstddef>
#include "ConfigTools.hpp"

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

class GameLogic
{
  // TODO: Currently with MapConfig, should be something else in the future
  using map_t = MapConfig;

public:
  GameLogic();
  GameLogic(GameLogic const &);
  GameLogic(GameLogic &&) = default;

  GameLogic &operator=(GameLogic const &);
  GameLogic &operator=(GameLogic &&) = default;

  ~GameLogic();

  // General configuration
  void run(); // Thread

  // Stop current game, and play the next scheduled map
  void nextMap();

  // GamePlayer
  std::size_t getCurrentPlayers() const;
  std::size_t getCurrentHumanPlayers() const;
  std::size_t getCurrentAIs() const;
  std::size_t getCurrentSpectator() const;

  // Maps
  map_t const &getCurrentMap() const;

  void addHumanPlayer();

private:
  enum class GameState : std::uint16_t
  {
    LOADING,
    PLAYING
  };

  void setUp();

  void addSpectator();
  void addAI();
  void deleteAI();

  void loadMap();

  void setState(GameState const state);

  void loadingState();
  void playingState();

  // General configuration
  std::atomic<bool> m_running;
  std::size_t       m_maxPlayers;
  std::size_t       m_currentHumanPlayers;
  std::size_t       m_currentAIs;
  std::size_t       m_currentSpectators;

  // TODO: GameData ?
  std::vector<map_t>           m_maps;
  std::vector<map_t>::iterator m_currentMap;
  GameState                    m_prevState;
  GameState                    m_state;
};

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !GAME_LOGIC_HPP_
