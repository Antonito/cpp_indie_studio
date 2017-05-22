#include "pakpak_stdafx.hpp"

namespace game
{
  PathPoint::PathPoint() : m_points(Ogre::Vector3(0, 0, 0), Ogre::Vector3(0, 0, 0))
  {
  }

  PathPoint::PathPoint(Ogre::Vector3 const &first, Ogre::Vector3 const &second)
      : m_points(first, second)
  {
  }

  PathPoint::PathPoint(PathPoint const &that) : m_points(that.m_points)
  {
  }

  PathPoint::PathPoint(PathPoint &&that) : m_points(std::move(that.m_points))
  {
  }

  PathPoint::~PathPoint()
  {
  }

  PathPoint &PathPoint::operator=(PathPoint const &that)
  {
    if (this == &that)
      return (*this);
    m_points = that.m_points;
    return (*this);
  }

  PathPoint &PathPoint::operator=(PathPoint &&that)
  {
    if (this == &that)
      return (*this);
    m_points = std::move(that.m_points);
    return (*this);
  }
}
