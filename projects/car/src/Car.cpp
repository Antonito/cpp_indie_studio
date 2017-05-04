//
// Created by duhieu_b on 02/05/17.
//

#include <vector>
#include <cstdint>
#include <sys/param.h>
#include <stdint-gcc.h>
#include "../include/Car.hpp"

const std::vector<Wheel> &Car::getWheels() const
{
  return m_wheels;
}

void Car::setWheels(const std::vector<Wheel> &p_wheels)
{
  m_wheels = p_wheels;
}

double Car::getSpeed() const
{
  return m_speed;
}

void Car::setSpeed(double p_speed)
{
  m_speed = p_speed;
}

int32_t Car::getHealth() const
{
  return m_health;
}

void Car::setHealth(int32_t p_health)
{
  m_health = p_health;
}

void Car::takeBonus(Bonus p_bonus)
{
  m_bonus = p_bonus;
}

void Car::takeDamage(std::int32_t p_damage)
{
  m_health -= p_damage;
}

std::int32_t Car::getResistance() const
{
  return m_resistance;
}

void Car::setResistance(std::int32_t p_resistance)
{
  m_resistance = p_resistance;
}
