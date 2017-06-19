#ifndef INDIE_MAP_HPP_
#define INDIE_MAP_HPP_

#include <string>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreSceneManager.h>
#include "PathPoint.hpp"
#include "Metadata.hpp"

namespace game
{
  class GameData;

  class Map
  {
  public:
    Map() = delete;
    Map(GameData &);
    Map(GameData &, std::string const &filename);
    Map(Map const &) = delete;
    Map(Map &&) = delete;
    ~Map();

    Map &operator=(Map const &) = delete;
    Map &operator=(Map &&) = delete;

    void                           loadFromFile(std::string filename);
    void                           unload();
    std::vector<Ogre::Vector3>	const &getNodes() const;
    OgreBulletDynamics::RigidBody *rigidBody();

#if defined(INDIE_MAP_EDITOR)
    void save() const;
    void saveAs(std::string const &filename) const;
    void addPoint(Ogre::Vector3 const &pt);
    void removePoint(std::size_t index);
    void removeSelectedPoint();
#endif // !INDIE_MAP_EDITOR

  private:
    struct MapData
    {
      MapData();
      struct Point
      {
	Point();
	Point(float _x, float _y, float _z);
	// clang-format off
	NOPE_SERIAL_MEMBER(
	    float, x,
	    float, y,
	    float, z)
	// clang-format on
      };

      struct Quaternion
      {
	Quaternion();
	Quaternion(float _x, float _y, float _z, float _w);
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
	Element();
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

    game::GameData &               m_gamedata;
    std::vector<Ogre::Vector3>     m_points;
    Ogre::Entity *                 m_map;
    Ogre::Entity *                 m_mapbox;
    Ogre::SceneNode *              m_node;
    OgreBulletDynamics::RigidBody *m_body;
#if defined(INDIE_MAP_EDITOR)
    std::string m_filename;
    std::size_t m_selectedPoint;
#endif // !INDIE_MAP_EDITOR

    // std::vector<MapElement> m_elements;
    // std::vector<MapBonus> m_bonus;
  };
}

#endif // !INDIE_MAP_HPP_
