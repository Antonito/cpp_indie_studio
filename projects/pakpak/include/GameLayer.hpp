#ifndef GAMELAYER_HPP_
#define GAMELAYER_HPP_

#include <cstddef>

namespace game
{
  struct GameLayer
  {
    enum
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
  };
}

#endif // !GAMELAYER_HPP_