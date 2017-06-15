//
// Created by duhieu_b on 04/05/17.
//

#include "Wheel.hpp"

double Wheel::getAdherence() const
{
  return m_adherence;
}

void Wheel::setAdherence(double const p_adherence)
{
  m_adherence = p_adherence;
}

double Wheel::getDirection() const
{
  return m_direction;
}

void Wheel::setDirection(double const p_direction)
{
  m_direction = p_direction;
}

double Wheel::getRayon() const
{
  return m_rayon;
}

void Wheel::setRayon(double const p_rayon)
{
  m_rayon = p_rayon;
}

Style const &Wheel::getStyle() const
{
  return m_style;
}

void Wheel::setStyle(Style const& p_style)
{
  m_style = p_style;
}
