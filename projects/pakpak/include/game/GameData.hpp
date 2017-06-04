#ifndef GAMEDATA_HPP_
#define GAMEDATA_HPP_

#include <vector>
#include <cstdint>
#include <chrono>
#include <OGRE/OgreSceneManager.h>
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

    void startTime();

    void update();

    Ogre::Camera *createCamera(std::string const &name);
    Ogre::Entity *createEntity(std::string const &name);
    Ogre::SceneNode *createSceneNode();

    Ogre::SceneManager *sceneMgr();

  private:
    Ogre::SceneManager *                                        m_sceneMgr;
    std::vector<PlayerData>                                     m_players;
    Map                                                         m_map;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
  };
}

#endif // !GAMEDATA_HPP_
