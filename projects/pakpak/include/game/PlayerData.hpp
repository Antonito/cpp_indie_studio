#ifndef PLAYERDATA_HPP_
#define PLAYERDATA_HPP_

#include <memory>
#include <OGRE/OgreVector3.h>

namespace game
{
    class ACar;
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

    std::size_t getRank() const;
    void        setRank(std::size_t);

    bool getFinished() const;
    void setFinished(bool);

  private:
    std::unique_ptr<ACar> m_car;
    int                   m_score;
    std::int32_t          m_currentCheckpoint;
    std::size_t           m_rank;
    bool                  m_finished;
  };
}

#endif // !PLAYERDATA_HPP_
