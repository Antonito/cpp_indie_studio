#ifndef GAMELAYER_HPP_
#define GAMELAYER_HPP_

namespace game
{
  enum class GameLayer
  {
    Loading,
    PreGame,
    InGame,
    GameGUI,
    Spectator,
    SpecGUI,
    PostGame,
    Score,
    Chat,
    Menu,
    NbLayer
  };
}

#endif // !GAMELAYER_HPP_