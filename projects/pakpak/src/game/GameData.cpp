#include "pakpak_stdafx.hpp"

namespace game
{
  GameData::GameData()
      : m_sceneMgr(Ogre::Root::getSingleton().createSceneManager(
            "DefaultSceneManager", "Game scene manager")),
        m_players(), m_world(nullptr),
#ifdef DEBUG
        m_debugDrawer(nullptr),
#endif
        m_bodies(), m_shapes(), m_map(), m_startTime(), m_laps(1),
        m_finalRanking(), m_localPlayerNb(0)
  {
    m_sceneMgr->getRootSceneNode()->createChildSceneNode("debugDrawer",
                                                         Ogre::Vector3::ZERO);
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
	std::int32_t checkpt = p.getCheckPoint() + 1;

	if (!p.getFinished() && m_map->getNbCheckPoint() != 0 &&
	    (checkpt / m_map->getNbCheckPoint()) >= m_laps)
	  {
	    p.setFinished(true);
	  }
	std::vector<int32_t> ranking = m_map->getPlayerOrder();
	for (std::size_t i = 0; i < ranking.size(); ++i)
	  {
	    if (ranking[i] < static_cast<std::int32_t>(m_players.size()))
	      m_players[static_cast<std::size_t>(ranking[i])].setRank(i);
	  }
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
    assert(m_map.get() != nullptr);
    return (*m_map);
  }

  Map const &GameData::map() const
  {
    assert(m_map.get() != nullptr);
    return (*m_map);
  }

  std::int32_t GameData::getLaps() const
  {
    return (m_laps);
  }

  void GameData::setLaps(std::int32_t laps)
  {
    m_laps = laps;
  }

  void GameData::resetPhysicWorld()
  {
    this->clearPhysicWorld();
    m_world = std::make_unique<OgreBulletDynamics::DynamicsWorld>(
        m_sceneMgr,
        Ogre::AxisAlignedBox(Ogre::Vector3(-100000000, -100000000, -100000000),
                             Ogre::Vector3(100000000, 100000000, 100000000)),
        Ogre::Vector3(0.0f, -9.81f * 80, 0.0f));

    // todo: move in Map
    m_sceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
#ifdef DEBUG
    m_debugDrawer = std::make_unique<OgreBulletCollisions::DebugDrawer>();
    m_debugDrawer->setDrawWireframe(true);
    m_world->setDebugDrawer(m_debugDrawer.get());
    m_world->setShowDebugShapes(true);

    Ogre::SceneNode *node = m_sceneMgr->getSceneNode("debugDrawer");
    node->attachObject(
        static_cast<Ogre::SimpleRenderable *>(m_debugDrawer.get()));
#endif
  }

  void GameData::clearPhysicWorld()
  {
    m_bodies.clear();
    m_shapes.clear();
    m_world.reset();
  }

  void GameData::addFinalPlayer(std::uint16_t id)
  {
    m_finalRanking.push_back(static_cast<std::uint32_t>(id));
  }

  std::uint32_t GameData::getFinalPlayerPosition(std::uint16_t id)
  {
    for (std::uint32_t i = 0; i < m_finalRanking.size(); ++i)
      {
	if (m_finalRanking[i] == id)
	  return (i + 1);
      }
    return 0;
  }

  void GameData::setMap(std::string const &mapName)
  {
    m_map = std::make_unique<Map>(*this, "./deps/indie_resource/maps/" +
                                             mapName + "/map.dat");
  }
  std::vector<PlayerData> &GameData::getPlayers()
  {
    return (m_players);
  }

    void GameData::setLocalPlayerNb(std::size_t nb)
    {
      m_localPlayerNb = nb;
    }

    std::size_t GameData::getLocalPlayerNb() const
    {
      return m_localPlayerNb;
    }
}