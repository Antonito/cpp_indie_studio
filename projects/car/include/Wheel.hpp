//
// Created by duhieu_b on 04/05/17.
//

#ifndef CPP_INDIE_STUDIO_WHEEL_HPP
#define CPP_INDIE_STUDIO_WHEEL_HPP

class Wheel : public IDrawable, public Object
{
public:
  Wheel() = default;
  Wheel(Wheel const &) = default;
  Wheel(Wheel &&) = delete;
  Wheel &operator=(Wheel &) = delete;
  Wheel &operator=(Wheel &&) = delete;

  double getAdherence() const;
  void setAdherence(double m_adherence);
  double getDirection() const;
  void setDirection(double m_direction);
  double getRayon() const;
  void setRayon(double m_rayon);
  const Style &getStyle() const;
  void setM_style(const Style &m_style);

private:
  double m_adherence;
  double m_direction;
  double m_rayon;
  Style  m_style;
};

#endif // CPP_INDIE_STUDIO_WHEEL_HPP
