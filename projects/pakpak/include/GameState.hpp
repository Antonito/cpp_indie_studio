#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <cstdint>

namespace core
{
  enum class GameState : std::int8_t
  {
    None = -1,
    Splash,
    Menu,
    InGame,
    Quit,
    NbGameState
  };

  enum class MenuState : std::int8_t
  {
    None = -1,
    MainMenu,
    Option,
    Keymap,
    SoloPlayerGame,
    MultiPlayerGame,
    Score,
    Quit,
    PopError,
    NbMenuState
  };

  enum class InGameState : std::int8_t
  {
    None = -1,
    Menu,
    Chat,
    Game,
    Start,
    End,
    Spectator,
    NbGameState
  };
}

#endif // !GAMESTATE_HPP_
