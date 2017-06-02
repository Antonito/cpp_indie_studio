#ifndef GAMEDATA_HPP_
#define GAMEDATA_HPP_

#include <vector>
#include <cstdint>
#include <OGRE/OgreSceneManager.h>
#include <OgreBulletDynamicsWorld.h>
#include <Debug/OgreBulletCollisionsDebugDrawer.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <OgreBulletCollisionsShape.h>
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

    PlayerData &      operator[](std::size_t);
    PlayerData const &operator[](std::size_t) const;

    void        setPlayerNb(std::size_t);
    std::size_t getPlayerNb() const;

    void update();

    Ogre::Camera *   createCamera(std::string const &name);
    Ogre::Entity *   createEntity(std::string const &name);
    Ogre::SceneNode *createSceneNode();

    Ogre::SceneManager *               sceneMgr();
    OgreBulletDynamics::DynamicsWorld *physicWorld();

    OgreBulletDynamics::RigidBody *
        addPhysicEntity(std::unique_ptr<OgreBulletCollisions::CollisionShape>,
                        std::string const &);

  private:
    Ogre::SceneManager *                               m_sceneMgr;
    std::vector<PlayerData>                            m_players;
    Map                                                m_map;
    std::unique_ptr<OgreBulletDynamics::DynamicsWorld> m_world;
#ifdef DEBUG
    std::unique_ptr<OgreBulletCollisions::DebugDrawer> m_debugDrawer;
#endif
    std::vector<std::unique_ptr<OgreBulletDynamics::RigidBody>> m_bodies;
    std::vector<std::unique_ptr<OgreBulletCollisions::CollisionShape>>
        m_shapes;
  };
}

#endif // !GAMEDATA_HPP_
