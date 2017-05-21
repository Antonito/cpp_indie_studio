#ifndef EMPTYCAR_HPP_
#define EMPTYCAR_HPP_

#include <OGRE/OgreVector3.h>
#include "ACar.hpp"

namespace game
{
  class EmptyCar final : public ACar
  {
  public:
    EmptyCar() = delete;
    EmptyCar(Ogre::SceneManager *sceneMgr, Ogre::Vector3 pos,
             Ogre::Vector3 dir);
    EmptyCar(EmptyCar const &) = delete;
    EmptyCar(EmptyCar &&) = delete;
    virtual ~EmptyCar();
  };
}

#endif // !EMPTYCAR_HPP_
