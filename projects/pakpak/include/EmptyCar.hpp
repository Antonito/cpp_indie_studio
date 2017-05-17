#ifndef EMPTYCAR_HPP_
#define EMPTYCAR_HPP_

#include <OGRE/OgreVector3.h>
#include "ACar.hpp"

namespace game
{
  class EmptyCar final : public ACar
  {
  public:
    EmptyCar();
    EmptyCar(Ogre::Vector3 pos, Ogre::Vector3 dir, Ogre::Vector3 mov,
             float speed);
    EmptyCar(EmptyCar const &) = delete;
    EmptyCar(EmptyCar &&) = delete;
    virtual ~EmptyCar();

    virtual Ogre::Vector3 const &position() const;
    virtual Ogre::Vector3 const &direction() const;
    virtual Ogre::Vector3 const &movement() const;
    virtual float const &        speed() const;
  };
}

#endif // !EMPTYCAR_HPP_
