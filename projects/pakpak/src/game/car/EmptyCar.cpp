#include "pakpak_stdafx.hpp"

namespace game
{
  EmptyCar::EmptyCar(game::GameData &gamedata, Ogre::Vector3 pos,
                     Ogre::Vector3 dir)
      : ACar(gamedata, "Jeep_default.mesh", pos, dir)
  {
  }

  EmptyCar::~EmptyCar()
  {
  }
}
