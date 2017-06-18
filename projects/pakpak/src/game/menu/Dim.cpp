//
// Created by brout_m on 16/06/17.
//

#include "pakpak_stdafx.hpp"

namespace resizer
{

  Dim::Dim() : m_x(0), m_y(0), m_width(0), m_height(0)
  {
  }

  Dim::Dim(float x, float y, float width, float height, float pWidth,
           float pHeight)
      : m_x(x / pWidth), m_y(y / pHeight), m_width(width / pWidth),
        m_height(height / pHeight)
  {
  }

  Dim::Dim(Dim const &d) :
    m_x(d.m_x), m_y(d.m_y), m_width(d.m_width), m_height(d.m_height)
  {
  }

  Dim &Dim::operator=(Dim const &d)
  {
    m_x = d.m_x;
    m_y = d.m_y;
    m_width = d.m_width;
    m_height = d.m_height;
    return *this;
  }
}