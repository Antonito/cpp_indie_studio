//
// Created by duhieu_b on 02/05/17.
//

#ifndef CPP_INDIE_STUDIO_CAR_HPP
#define CPP_INDIE_STUDIO_CAR_HPP

#include <iostream>
#include <cstdint>
#include <vector>
#include "Wheel.hpp"

class Car : public IDrawable, public Objects
{
public:
  Car() = default;
  Car(Car const &) = default;
  Car(Car &&) = delete;
  Car &operator=(Car &) = delete;
  Car &operator=(Car &&) = delete;

  const std::vector<Wheel> &getWheels() const;
  void                      setWheels(std::vector<Wheel> const &);
  double                    getSpeed() const;
  void                      setSpeed(double const);
  std::int32_t              getHealth() const;
  void                      setHealth(std::int32_t const);
  std::int32_t              getResistance() const;
  void                      setResistance(std::int32_t const);

  void takeBonus(Bonus const);
  void takeDamage(std::int32_t const);

private:
  std::vector<Wheel> m_wheels;
  double             m_speed;
  std::int32_t       m_resistance;
  std::int32_t       m_health;
  Bonus              m_bonus;
};

#endif // CPP_INDIE_STUDIO_CAR_HPP
