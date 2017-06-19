#ifndef PLAYERDATA_HPP_
#define PLAYERDATA_HPP_

#include <memory>
#include <OGRE/OgreVector3.h>
#include "ACar.hpp"

namespace game
{
  class PlayerData
  {
  public:
    PlayerData();
    PlayerData(PlayerData const &) = delete;
    PlayerData(PlayerData &&);
    ~PlayerData();

    PlayerData &operator=(PlayerData const &) = delete;
    PlayerData &operator=(PlayerData &&) = delete;

    void setCar(std::unique_ptr<ACar> &&car);
    void setScore(int);

    int         getScore() const;
    bool        hasCar() const;
    ACar &      car();
    ACar const &car() const;

    std::int32_t getCheckPoint() const;
    void         nextCheckPoint();

  private:
    std::unique_ptr<ACar> m_car;
    int                   m_score;
    std::int32_t          m_currentCheckpoint;
  };
}

#endif // !PLAYERDATA_HPP_
