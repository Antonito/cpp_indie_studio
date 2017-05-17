#include "pakpak_stdafx.hpp"

namespace game
{
  ACar::ACar() : m_pos(0, 0, 0), m_dir(0, 0, 0), m_mov(0, 0, 0), m_speed(0)
  {
  }

  ACar::ACar(Ogre::Vector3 pos, Ogre::Vector3 dir, Ogre::Vector3 mov,
             float speed)
      : m_pos(pos), m_dir(dir), m_mov(mov), m_speed(speed)
  {
  }

  ACar::~ACar()
  {
  }
}