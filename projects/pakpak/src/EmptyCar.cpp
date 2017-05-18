#include "pakpak_stdafx.hpp"

namespace game
{
  EmptyCar::EmptyCar() : ACar()
  {
  }

  EmptyCar::EmptyCar(Ogre::Vector3 pos, Ogre::Vector3 dir, Ogre::Vector3 mov,
                     double speed)
      : ACar(pos, dir, mov, speed)
  {
  }

  EmptyCar::~EmptyCar()
  {
  }

  Ogre::Vector3 const &EmptyCar::position() const
  {
    return (m_pos);
  }

  Ogre::Vector3 const &EmptyCar::direction() const
  {
    return (m_dir);
  }

  Ogre::Vector3 const &EmptyCar::movement() const
  {
    return (m_mov);
  }

  double const &EmptyCar::speed() const
  {
    return (m_speed);
  }

  void EmptyCar::position(Ogre::Vector3 const &position)
  {
    m_pos = position;
  }

  void EmptyCar::direction(Ogre::Vector3 const &direction)
  {
    m_dir = direction;
  }

  void EmptyCar::movement(Ogre::Vector3 const &movement)
  {
    m_mov = movement;
  }

  void EmptyCar::speed(double speed)
  {
    m_speed = speed;
  }

  void EmptyCar::create(GameData &gameData)
  {
    m_entity = gameData.createEntity("ogrehead.mesh");
    m_node = gameData.createSceneNode();
    m_node->attachObject(m_entity);
  }
}