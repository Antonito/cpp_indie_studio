#ifndef ACAR_HPP_
#define ACAR_HPP_

#include <OGRE/OgreVector3.h>

namespace game
{
  class GameData;

  class ACar
  {
  public:
    ACar();
    ACar(Ogre::Vector3 pos, Ogre::Vector3 dir, Ogre::Vector3 mov,
         double speed);
    ACar(ACar const &) = delete;
    ACar(ACar &&) = delete;
    virtual ~ACar();

    ACar &operator=(ACar const &) = delete;
    ACar &operator=(ACar &&) = delete;

    virtual void create(GameData &) = 0;

    virtual Ogre::Vector3 const &position() const = 0;
    virtual Ogre::Vector3 const &direction() const = 0;
    virtual Ogre::Vector3 const &movement() const = 0;
    virtual double const &       speed() const = 0;

    virtual void position(Ogre::Vector3 const &) = 0;
    virtual void direction(Ogre::Vector3 const &) = 0;
    virtual void movement(Ogre::Vector3 const &) = 0;
    virtual void speed(double) = 0;

  protected:
    Ogre::Vector3    m_pos;
    Ogre::Vector3    m_dir;
    Ogre::Vector3    m_mov;
    double           m_speed;
    Ogre::SceneNode *m_node;
    Ogre::Entity *   m_entity;
  };
}

#endif // !ACAR_HPP_