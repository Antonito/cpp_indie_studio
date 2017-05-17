#include "pakpak_stdafx.hpp"

namespace game
{
  EmptyCar::EmptyCar() : ACar()
  {
  }

  EmptyCar::EmptyCar(Ogre::Vector3 pos, Ogre::Vector3 dir, Ogre::Vector3 mov,
                     float speed)
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

  float const &EmptyCar::speed() const
  {
    return (m_speed);
  }
}