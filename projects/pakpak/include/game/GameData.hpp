#ifndef GAMEDATA_HPP_
#define GAMEDATA_HPP_

#include <vector>
#include <cstdint>
#include <OGRE/OgreSceneManager.h>

// Disable clang warning for templated class padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang            system_header
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Woverloaded-virtual"
#endif

#include <OgreBulletDynamicsWorld.h>
#include <Debug/OgreBulletCollisionsDebugDrawer.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <OgreBulletCollisionsShape.h>

// Disable clang warning for templated class padding
#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#include "PlayerData.hpp"
#include "Map.hpp"

namespace game
{
  class GameData
  {
  public:
    GameData();
    GameData(GameData const &) = delete;
    GameData(GameData &&) = delete;
    ~GameData();

    GameData &operator=(GameData const &) = delete;
    GameData &operator=(GameData &&) = delete;

    PlayerData &operator[](std::size_t);
    PlayerData const &operator[](std::size_t) const;

    void        setPlayerNb(std::size_t);
    std::size_t getPlayerNb() const;

    void update();

    Ogre::Camera *createCamera(std::string const &name);
    Ogre::Entity *createEntity(std::string const &name);
    Ogre::SceneNode *createSceneNode();

    Ogre::SceneManager *               sceneMgr();
    OgreBulletDynamics::DynamicsWorld *physicWorld();

#ifdef DEBUG
    OgreBulletCollisions::DebugDrawer *debugDrawer();
#endif // !DEBUG

    OgreBulletDynamics::RigidBody *
        addPhysicEntity(std::unique_ptr<OgreBulletCollisions::CollisionShape>,
                        std::string const &);
    Map &      map();
    Map const &map() const;

  private:
    Ogre::SceneManager *                               m_sceneMgr;
    std::vector<PlayerData>                            m_players;
    std::unique_ptr<OgreBulletDynamics::DynamicsWorld> m_world;
#ifdef DEBUG
    std::unique_ptr<OgreBulletCollisions::DebugDrawer> m_debugDrawer;
#endif
    std::vector<std::unique_ptr<OgreBulletDynamics::RigidBody>> m_bodies;
    std::vector<std::unique_ptr<OgreBulletCollisions::CollisionShape>>
        m_shapes;
    Map m_map;
  };
}

#endif // !GAMEDATA_HPP_
