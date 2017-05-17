#ifndef GAMEDATA_HPP_
#define GAMEDATA_HPP_

#include <vector>
#include <cstdint>
#include "PlayerData.hpp"

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

    void        setPlayerNb(std::int32_t);
    std::size_t getPlayerNb() const;

    void update();

  private:
    // m_sceneMgr;
    std::vector<PlayerData> m_players;
  };
}

#endif // !GAMEDATA_HPP_
