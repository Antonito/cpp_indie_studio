#ifndef ACAR_HPP_
#define ACAR_HPP_

#include <OGRE/OgreVector3.h>

namespace game
{
  class ACar
  {
  public:
    ACar();
    ACar(Ogre::Vector3 pos, Ogre::Vector3 dir, Ogre::Vector3 mov, float speed);
    ACar(ACar const &) = delete;
    ACar(ACar &&) = delete;
    virtual ~ACar();

    ACar &operator=(ACar const &) = delete;
    ACar &operator=(ACar &&) = delete;

    virtual Ogre::Vector3 const &position() const = 0;
    virtual Ogre::Vector3 const &direction() const = 0;
    virtual Ogre::Vector3 const &movement() const = 0;
    virtual float const &        speed() const = 0;

  protected:
    Ogre::Vector3 m_pos;
    Ogre::Vector3 m_dir;
    Ogre::Vector3 m_mov;
    float         m_speed;
  };
}

#endif // !ACAR_HPP_