#ifndef EMPTYCAR_HPP_
#define EMPTYCAR_HPP_

#include <OGRE/OgreVector3.h>
#include "ACar.hpp"

namespace game
{
  // TODO: REMOVE THAT CLASS
  class EmptyCar : public ACar
  {
  public:
    EmptyCar(){};

    virtual Ogre::Vector3 const &position() const
    {
      return (Ogre::Vector3(0, 0, 0));
    }
  };
}

#endif // !EMPTYCAR_HPP_
