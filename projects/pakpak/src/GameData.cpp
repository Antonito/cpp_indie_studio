#include "pakpak_stdafx.hpp"

namespace game
{
  GameData::GameData()
      : m_sceneMgr(Ogre::Root::getSingleton().createSceneManager(
            "DefaultSceneManager", "Game scene manager")),
        m_players()
  {
    // todo: move in Map
    m_sceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    m_sceneMgr->createLight("MainLight")->setPosition(20, 80, 50);
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

  void GameData::setPlayerNb(std::int32_t n)
  {
    m_players.resize(n);
  }

  std::size_t GameData::getPlayerNb() const
  {
    return (m_players.size());
  }

  void GameData::update()
  {
    // TODO: implements lol
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
}