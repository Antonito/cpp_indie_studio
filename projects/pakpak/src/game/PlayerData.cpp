#include "pakpak_stdafx.hpp"

namespace game
{
  PlayerData::PlayerData() : m_car(nullptr), m_score(0)
  {
  }

  PlayerData::PlayerData(PlayerData &&that)
      : m_car(std::move(that.m_car)), m_score(0)
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
}
