//
// Created by duhieu_b on 02/05/17.
//

#ifndef CPP_INDIE_STUDIO_CAR_HPP
#define CPP_INDIE_STUDIO_CAR_HPP

#include <iostream>
#include <cstdint>
#include <vector>
#include "Bonus.hpp"
#include "Wheel.hpp"

#define MAX_SPEED 100
#define MAX_ACC 5
#define MIN_ACC -5

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
  std::int32_t              getSpeed() const;
  void                      setSpeed(std::int32_t const);
  std::int32_t              getHealth() const;
  void                      setHealth(std::int32_t const);
  std::int32_t              getResistance() const;
  void                      setResistance(std::int32_t const);
  void                      setPosition(Position const);
  Position &                getPosition() const;

  void takeBonus(Bonus const);
  void takeDamage(std::int32_t const);
  void Accelerate();
  void Descelerate();
  void updateSpeed();
  void updatePosition();

private:
  std::vector<Wheel> m_wheels;
  std::int32_t       m_speed;
  std::int32_t       m_accelerate;
  std::int32_t       m_resistance;
  std::int32_t       m_health;
  Bonus              m_bonus;
  Position           m_position;
};

#endif // CPP_INDIE_STUDIO_CAR_HPP
