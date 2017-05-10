#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

namespace core
{
  enum class GameState
  {
    None = -1,
    Splash,
    MainMenu,
    Game,
    InGameMenu,
    NbGameState
  };
}

#endif // !GAMESTATE_HPP_