#ifndef PATHPOINT_HPP_
#define PATHPOINT_HPP_

#include <OGRE/OgreVector3.h>

namespace game
{
  class PathPoint
  {
  public:
    PathPoint();
    PathPoint(Ogre::Vector3 const &first, Ogre::Vector3 const &second);
    PathPoint(PathPoint const &);
    PathPoint(PathPoint &&);
    ~PathPoint();

    PathPoint &operator=(PathPoint const &);
    PathPoint &operator=(PathPoint &&);

  private:
    std::pair<Ogre::Vector3, Ogre::Vector3> m_points;
  };
}

#endif // !PATHPOINT_HPP_
