#ifndef COLLISION_HPP_
#define COLLISION_HPP_

#include <OGRE/OgreVector3.h>

namespace physic
{
  class Collision
  {
  public:
    Collision() = delete;
    Collision(Ogre::Vector3 const &point, Ogre::Vector3 const &norm,
              double depth);
    Collision(Collision const &) = default;
    Collision(Collision &&) = default;
    ~Collision();

    Collision &operator=(Collision const &) = default;
    Collision &operator=(Collision &&) = default;

    Ogre::Vector3 const &point() const;
    Ogre::Vector3 const &normale() const;
    double               depth() const;

  private:
    Ogre::Vector3 m_point;
    Ogre::Vector3 m_norm;
    double        m_depth;
  };
}

#endif // !COLLISION_HPP_