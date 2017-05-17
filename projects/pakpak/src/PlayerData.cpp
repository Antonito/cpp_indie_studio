#include "pakpak_stdafx.hpp"

namespace game
{
  PlayerData::PlayerData() : m_car(nullptr)
  {
  }

  PlayerData::~PlayerData()
  {
  }

  void PlayerData::setCar(std::unique_ptr<ACar> &&car)
  {
    m_car = std::move(car);
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