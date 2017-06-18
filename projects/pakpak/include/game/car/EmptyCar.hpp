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
    EmptyCar(game::GameData &gamedata, Ogre::Vector3 const &pos,
             Ogre::Quaternion const &dir);
    EmptyCar(EmptyCar const &) = delete;
    EmptyCar(EmptyCar &&) = delete;
    virtual ~EmptyCar();
  };
}

#endif // !EMPTYCAR_HPP_
