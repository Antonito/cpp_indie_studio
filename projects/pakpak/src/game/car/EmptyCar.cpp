#include "pakpak_stdafx.hpp"

namespace game
{
  EmptyCar::EmptyCar(Ogre::SceneManager *sceneMgr, Ogre::Vector3 pos,
                     Ogre::Vector3 dir)
      : ACar(sceneMgr, "ogrehead.mesh", pos, dir)
  {
  }

  EmptyCar::~EmptyCar()
  {
  }
}