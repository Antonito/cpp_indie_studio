#ifndef PLAYERDATA_HPP_
#define PLAYERDATA_HPP_

#include <chrono>
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
    PlayerData &operator=(PlayerData &&);

    void setCar(std::unique_ptr<ACar> &&car);
    void setScore(int);

    int         getScore() const;
    bool        hasCar() const;
    ACar &      car();
    ACar const &car() const;

    std::int32_t getCheckPoint() const;
    void         nextCheckPoint();

    std::size_t getRank() const;
    void        setRank(std::size_t);

    bool getFinished() const;
    void setFinished(bool);

    void setId(std::uint16_t const id);
    std::uint16_t getId() const;

    bool hasTimedOut() const;
    void updateLastAction();

  private:
    std::unique_ptr<ACar>                 m_car;
    int                                   m_score;
    std::int32_t                          m_currentCheckpoint;
    std::size_t                           m_rank;
    bool                                  m_finished;
    std::uint16_t                         m_id;
    std::chrono::system_clock::time_point m_lastAction;
  };
}

#endif // !PLAYERDATA_HPP_
