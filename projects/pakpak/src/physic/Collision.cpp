#include "pakpak_stdafx.hpp"

namespace physic
{
  Collision::Collision(Ogre::Vector3 const &point, Ogre::Vector3 const &norm,
                       double depth)
      : m_point(point), m_norm(norm), m_depth(depth)
  {
  }

  Collision::~Collision()
  {
  }

  Ogre::Vector3 const &Collision::point() const
  {
    return (m_point);
  }

  Ogre::Vector3 const &Collision::normale() const
  {
    return (m_norm);
  }

  double Collision::depth() const
  {
    return (m_depth);
  }
}