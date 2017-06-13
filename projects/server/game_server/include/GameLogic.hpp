#ifndef GAME_LOGIC_HPP_
#define GAME_LOGIC_HPP_

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

  GameLogic const &operator=(GameLogic const &);
  GameLogic &      operator=(GameLogic &&) = default;

private:
};

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !GAME_LOGIC_HPP_
