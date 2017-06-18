#include "pakpak_stdafx.hpp"

namespace game
{
  GameData::GameData()
      : m_sceneMgr(Ogre::Root::getSingleton().createSceneManager(
            "DefaultSceneManager", "Game scene manager")),
        m_players(),
        m_world(new OgreBulletDynamics::DynamicsWorld(
            m_sceneMgr, Ogre::AxisAlignedBox(
                            Ogre::Vector3(-100000000, -100000000, -100000000),
                            Ogre::Vector3(100000000, 100000000, 100000000)),
            Ogre::Vector3(0.0f, -9.81f * 80, 0.0f))),
#ifdef DEBUG
        m_debugDrawer(nullptr),
#endif
        m_bodies(), m_shapes(),
        m_map(*this, "./deps/indie_resource/maps/test/map.dat"), m_startTime()
  {
    // todo: move in Map
    m_sceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    m_sceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
    Ogre::Light *l = m_sceneMgr->createLight("MainLight");
    l->setPosition(20, 80, 50);
    l->setCastShadows(true);

#ifdef DEBUG
    m_debugDrawer = std::make_unique<OgreBulletCollisions::DebugDrawer>();
    m_debugDrawer->setDrawWireframe(true);
    m_world->setDebugDrawer(m_debugDrawer.get());
    m_world->setShowDebugShapes(true);

    Ogre::SceneNode *node =
        m_sceneMgr->getRootSceneNode()->createChildSceneNode(
            "debugDrawer", Ogre::Vector3::ZERO);
    node->attachObject(
        static_cast<Ogre::SimpleRenderable *>(m_debugDrawer.get()));
#endif
  }

  GameData::~GameData()
  {
  }

  PlayerData &GameData::operator[](std::size_t i)
  {
    return (m_players[i]);
  }

  PlayerData const &GameData::operator[](std::size_t i) const
  {
    return (m_players[i]);
  }

  void GameData::setPlayerNb(std::size_t n)
  {
    m_players.resize(n);
  }

  std::size_t GameData::getPlayerNb() const
  {
    return (m_players.size());
  }

  void GameData::startTime()
  {
    m_startTime = std::chrono::high_resolution_clock::now();
  }

  void GameData::update()
  {
    for (PlayerData &p : m_players)
      {
	p.car().update(1 / 60.0);
      }
  }

  Ogre::Camera *GameData::createCamera(std::string const &name)
  {
    return (m_sceneMgr->createCamera(name));
  }

  Ogre::Entity *GameData::createEntity(std::string const &name)
  {
    return (m_sceneMgr->createEntity(name));
  }
  Ogre::SceneNode *GameData::createSceneNode()
  {
    return (m_sceneMgr->getRootSceneNode()->createChildSceneNode());
  }

  Ogre::SceneManager *GameData::sceneMgr()
  {
    return (m_sceneMgr);
  }

  OgreBulletDynamics::DynamicsWorld *GameData::physicWorld()
  {
    return (m_world.get());
  }

#ifdef DEBUG
  OgreBulletCollisions::DebugDrawer *GameData::debugDrawer()
  {
    return (m_debugDrawer.get());
  }
#endif // !DEBUG

  OgreBulletDynamics::RigidBody *GameData::addPhysicEntity(
      std::unique_ptr<OgreBulletCollisions::CollisionShape> box,
      std::string const &                                   bodyname)
  {
    std::unique_ptr<OgreBulletDynamics::RigidBody> body(
        new OgreBulletDynamics::RigidBody(bodyname, m_world.get()));
    OgreBulletDynamics::RigidBody *ptr = body.get();

    m_shapes.push_back(std::move(box));
    m_bodies.push_back(std::move(body));

    return (ptr);
  }

  Map &GameData::map()
  {
    return (m_map);
  }

  Map const &GameData::map() const
  {
    return (m_map);
  }

    void GameData::setIaNb(std::size_t n)
    {
      m_ia.resize(n);
    }

    size_t GameData::getIaNb() const
    {
      return m_ia.size();
    }

}
