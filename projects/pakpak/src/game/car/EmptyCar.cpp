#include "pakpak_stdafx.hpp"

namespace game
{
  EmptyCar::EmptyCar(game::GameData &gamedata, Ogre::Vector3 const &pos,
                     Ogre::Quaternion const &dir)
      : ACar(gamedata, "Jeep_default.mesh", pos, dir)
  {
  }

  EmptyCar::~EmptyCar()
  {
  }
}
