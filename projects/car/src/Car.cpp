//
// Created by duhieu_b on 02/05/17.
//

#include <vector>
#include <cstdint>
#include "Car.hpp"

std::vector<Wheel> const &Car::getWheels() const
{
  return m_wheels;
}

void Car::setWheels(std::vector<Wheel> const& p_wheels)
{
  m_wheels = p_wheels;
}

double Car::getSpeed() const
{
  return m_speed;
}

void Car::setSpeed(double const p_speed)
{
  m_speed = p_speed;
}

std::int32_t Car::getHealth() const
{
  return m_health;
}

void Car::setHealth(std::int32_t const p_health)
{
  m_health = p_health;
}

void Car::takeBonus(Bonus const p_bonus)
{
  m_bonus = p_bonus;
}

void Car::takeDamage(std::int32_t const p_damage)
{
  m_health -= p_damage;
}

std::int32_t Car::getResistance() const
{
  return m_resistance;
}

void Car::setResistance(std::int32_t const p_resistance)
{
  m_resistance = p_resistance;
}
