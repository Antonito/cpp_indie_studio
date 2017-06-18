#ifndef MAP_HPP_
#define MAP_HPP_

#include <string>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreSceneManager.h>
#include <game/GameData.hpp>
#include "PathPoint.hpp"
#include "Metadata.hpp"

namespace game
{
  class Map
  {
  public:
    Map() = delete;
    Map(game::GameData &gamedata);
    Map(game::GameData &gamedata, std::string const &filename);
    Map(Map const &) = delete;
    Map(Map &&) = delete;
    ~Map();

    Map &operator=(Map const &) = delete;
    Map &operator=(Map &&) = delete;

    void                           loadFromFile(std::string filename);
    void                           unload();
    std::vector<Ogre::Vector3>	const &getNodes() const;
    OgreBulletDynamics::RigidBody *rigidBody();

  private:
    struct MapData
    {
      MapData();
      struct Point
      {
	Point();
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
    std::vector<PathPoint>         m_points;
    Ogre::Entity *                 m_map;
    Ogre::SceneNode *              m_node;
    OgreBulletDynamics::RigidBody *m_body;
    // std::vector<MapElement> m_elements;
    // std::vector<MapBonus> m_bonus;
  };
}

#endif // !MAP_HPP_
