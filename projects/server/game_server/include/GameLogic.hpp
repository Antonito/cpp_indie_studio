#ifndef GAME_LOGIC_HPP_
#define GAME_LOGIC_HPP_

#include <cstddef>

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

class GameLogic
{
public:
  GameLogic();
  GameLogic(GameLogic const &);
  GameLogic(GameLogic &&) = default;

  GameLogic &operator=(GameLogic const &);
  GameLogic &operator=(GameLogic &&) = default;

  ~GameLogic();

  // General configuration
  void setUp();
  void run();

  // Stop current game, and play the next scheduled map
  void nextMap();

  // GamePlayer
  std::size_t getCurrentPlayers() const;
  std::size_t getCurrentHumanPlayers() const;
  std::size_t getCurrentAIs() const;
  std::size_t getCurrentSpectator() const;

  void addHumanPlayer();

private:
  void addSpectator();
  void addAI();

  // TODO: GameData ?
};

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !GAME_LOGIC_HPP_
