#include "pakpak_stdafx.hpp"

namespace game
{
  GameData::GameData() : m_players()
  {
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
}