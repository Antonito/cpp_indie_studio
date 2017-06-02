#ifndef ACAR_HPP_
#define ACAR_HPP_

#include <OGRE/OgreVector3.h>

namespace game
{
  class GameData;

  class ACar
  {
  public:
    ACar() = delete;
    ACar(ACar const &) = delete;
    ACar(ACar &&) = delete;
    virtual ~ACar();

    ACar &operator=(ACar const &) = delete;
    ACar &operator=(ACar &&) = delete;

    Ogre::Vector3 const &position() const;
    Ogre::Vector3 const &direction() const;
    Ogre::Vector3 const &movement() const;
    double               speed() const;

    void move(double);
    void turn(double);

    void update(double);

    Ogre::Camera *getCamera() const;

  protected:
    ACar(game::GameData &gamedata, std::string const &mesh,
         Ogre::Vector3 const &pos, Ogre::Vector3 const &dir);

    Ogre::Vector3 m_pos;
    Ogre::Vector3 m_dir;
    Ogre::Vector3 m_mov;
    double        m_speed;

    double m_tryMoving;
    double m_tryTurning;

    Ogre::SceneNode *m_node;
    Ogre::SceneNode *m_carNode;
    Ogre::Entity *   m_entity;
    Ogre::Camera *   m_camera;
  };
}

#endif // !ACAR_HPP_
