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
    virtual ~EmptyCar()
    {
    }

    virtual Ogre::Vector3 const &position() const
    {
      return (m_pos);
    }
  };
}

#endif // !EMPTYCAR_HPP_
