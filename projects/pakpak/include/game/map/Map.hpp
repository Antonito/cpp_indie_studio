#ifndef INDIE_MAP_HPP_
#define INDIE_MAP_HPP_

#include <string>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreSceneManager.h>
#include "PathPoint.hpp"
#include "Metadata.hpp"
#include "CheckPoint.hpp"

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

    void loadFromFile(std::string filename);
    void                              unload();
    std::vector<Ogre::Vector3> const &getNodes() const;
    OgreBulletDynamics::RigidBody *   rigidBody();

#if defined(INDIE_MAP_EDITOR)
    void save() const;
    void saveAs(std::string const &filename) const;
    void addPoint(Ogre::Vector3 const &pt);
    void removePoint(std::size_t index);
    void removeSelectedPoint();
#endif // !INDIE_MAP_EDITOR

    std::vector<std::int32_t>      getPlayerOrder();
    std::int32_t                   getNbCheckPoint() const;
    std::vector<CheckPoint> const &getCheckPoints() const;

  private:
    struct MapData
    {
      MapData();
      struct Point
      {
	Point();
	Point(Point const &) = delete;
	Point(Point &&);

	Point(std::int32_t _x, std::int32_t _y, std::int32_t _z);

	Point &operator=(Point const &) = delete;
	Point &operator=(Point &&);

	// clang-format off
	NOPE_SERIAL_MEMBER(
	    std::int32_t, x,
	    std::int32_t, y,
	    std::int32_t, z)
	// clang-format on
      };

      struct Quaternion
      {
	Quaternion();
	Quaternion(Quaternion const &) = delete;
	Quaternion(Quaternion &&);
	Quaternion(std::int32_t _x, std::int32_t _y, std::int32_t _z,
	           std::int32_t _w);

	Quaternion &operator=(Quaternion const &) = delete;
	Quaternion &operator=(Quaternion &&);

	// clang-format off
	NOPE_SERIAL_MEMBER(
	    std::int32_t, x,
	    std::int32_t, y,
	    std::int32_t, z,
	    std::int32_t, w)
	// clang-format on
      };

      struct Element
      {
	Element();
	Element(Element const &) = delete;
	Element(Element &&);

	Element &operator=(Element const &) = delete;
	Element &operator=(Element &&);
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
    std::vector<CheckPoint>        m_checkpoints;
    Ogre::Entity *                 m_map;
    Ogre::Entity *                 m_mapbox;
    Ogre::SceneNode *              m_node;
    OgreBulletDynamics::RigidBody *m_body;

    std::vector<Ogre::Light *> m_lights;
#if defined(INDIE_MAP_EDITOR)
    std::string m_filename;
    std::size_t m_selectedPoint;
#endif // !INDIE_MAP_EDITOR
  };
}

#endif // !INDIE_MAP_HPP_
