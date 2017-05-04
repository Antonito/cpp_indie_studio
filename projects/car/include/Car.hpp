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
  void                      setWheels(const std::vector<Wheel> &);
  double                    getSpeed() const;
  void                      setSpeed(double);
  std::int32_t              getHealth() const;
  void                      setHealth(std::int32_t);
  std::int32_t              getResistance() const;
  void                      setResistance(std::int32_t);

  void takeBonus(Bonus);
  void takeDamage(std::int32_t);

private:
  std::vector<Wheel> m_wheels;
  double             m_speed;
  std::int32_t       m_resistance;
  std::int32_t       m_health;
  Bonus              m_bonus;
};

#endif // CPP_INDIE_STUDIO_CAR_HPP
