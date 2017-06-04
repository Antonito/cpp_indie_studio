#include "pakpak_stdafx.hpp"

namespace game
{
  GameData::GameData()
      : m_sceneMgr(Ogre::Root::getSingleton().createSceneManager(
            "DefaultSceneManager", "Game scene manager")),
        m_players(), m_map(m_sceneMgr, "../indie_resource/maps/test/map.dat"),
        m_startTime()
  {
    // todo: move in Map
    m_sceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    m_sceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    Ogre::Light *l = m_sceneMgr->createLight("MainLight");
    l->setPosition(20, 80, 50);
    l->setCastShadows(true);
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
}
