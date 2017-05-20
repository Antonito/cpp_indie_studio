#ifndef MAP_HPP_
#define MAP_HPP_

#include <string>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreSceneManager.h>
#include "PathPoint.hpp"
#include "Metadata.hpp"

namespace game
{
  class Map
  {
  public:
    Map() = delete;
    Map(Ogre::SceneManager *sceneMgr);
    Map(Ogre::SceneManager *sceneMgr, std::string const &filename);
    Map(Map const &) = delete;
    Map(Map &&) = delete;
    ~Map();

    Map &operator=(Map const &) = delete;
    Map &operator=(Map &&) = delete;

    void loadFromFile(std::string filename);
    void unload();

  private:
    struct MapData
    {
      MapData()
      {
      }
      struct Point
      {
	Point()
	{
	}
	// clang-format off
	NOPE_SERIAL_MEMBER(
	    float, x,
	    float, y,
	    float, z)
	// clang-format on
      };

      struct Quaternion
      {
	// clang-format off
	NOPE_SERIAL_MEMBER(
	    float, x,
	    float, y,
	    float, z,
	    float, w)
	// clang-format on
      };

      struct Element
      {
	// clang-format off
	  NOPE_SERIAL_MEMBER(
	      Point,        pos,
	      Quaternion,   rot,
	      std::int32_t, type)
	// clang-format on
      };

      // clang-format off
      NOPE_SERIAL_MEMBER(
	  std::vector<Point>,   points,
	  std::vector<Element>, elements)
      // clang-format on
    };

    Ogre::SceneManager *   m_sceneMgr;
    std::vector<PathPoint> m_points;
    Ogre::Entity *         m_map;
    // std::vector<MapElement> m_elements;
    // std::vector<MapBonus> m_bonus;
  };
}

#endif // !MAP_HPP_