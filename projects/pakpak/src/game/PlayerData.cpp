#include "pakpak_stdafx.hpp"

namespace game
{
  PlayerData::PlayerData()
      : m_car(nullptr), m_score(0), m_currentCheckpoint(0), m_rank(0),
        m_finished(false), m_id(0)
  {
  }

  PlayerData::PlayerData(PlayerData &&that)
      : m_car(std::move(that.m_car)), m_score(0),
        m_currentCheckpoint(that.m_currentCheckpoint), m_rank(that.m_rank),
        m_finished(that.m_finished), m_id(that.m_id)
  {
  }

  PlayerData::~PlayerData()
  {
  }

  void PlayerData::setCar(std::unique_ptr<ACar> &&car)
  {
    m_car = std::move(car);
  }

  void PlayerData::setScore(int score)
  {
    m_score = score;
  }

  int PlayerData::getScore() const
  {
    return (m_score);
  }

  bool PlayerData::hasCar() const
  {
    return (m_car.get() != nullptr);
  }

  ACar &PlayerData::car()
  {
    assert(m_car.get() != nullptr && "Trying to access a null-set car");
    return (*m_car);
  }

  ACar const &PlayerData::car() const
  {
    assert(m_car.get() != nullptr && "Trying to access a null-set car");
    return (*m_car);
  }
  std::int32_t PlayerData::getCheckPoint() const
  {
    return (m_currentCheckpoint);
  }

  void PlayerData::nextCheckPoint()
  {
    ++m_currentCheckpoint;
    nope::log::Log(Debug) << "Players passed checkpoint "
                          << m_currentCheckpoint;
  }

  std::size_t PlayerData::getRank() const
  {
    return (m_rank);
  }

  void PlayerData::setRank(std::size_t rank)
  {
    m_rank = rank;
  }

  bool PlayerData::getFinished() const
  {
    return (m_finished);
  }

  void PlayerData::setFinished(bool finished)
  {
    nope::log::Log(Debug) << "FINISHED !!!!";
    m_finished = finished;
  }

  void PlayerData::setId(std::uint16_t const id)
  {
    m_id = id;
  }

  std::uint16_t PlayerData::getId() const
  {
    return (m_id);
  }
}
