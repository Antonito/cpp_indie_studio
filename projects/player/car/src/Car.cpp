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

std::int32_t Car::getSpeed() const
{
  return m_speed;
}

void Car::setSpeed(std::int32_t const p_speed)
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

void Car::setPosition(Position const p_pos)
{
  m_position = p_pos;
}

Position &Car::getPosition() const
{
  return m_position;
}

void Car::updateSpeed()
{
  if (m_speed + m_accelerate > 0 && m_speed + m_accelerate < MAX_SPEED)
    m_speed += m_accelerate;
  else if (m_speed + m_accelerate < 0)
    m_speed = 0;
  else if (m_speed + m_accelerate > MAX_SPEED)
    m_speed = MAX_SPEED;
}

void Car::updatePosition()
{
  //TODO
  //Relation between wheel direction, wheel aderence, speed and position
}

void Car::Accelerate()
{
  m_accelerate = (m_accelerate == MAX_ACC) ? m_accelerate : m_accelerate + 1;
}

void Car::Descelerate()
{
  m_accelerate = (m_accelerate == MIN_ACC) ? m_accelerate : m_accelerate - 1;
}

