//
// Created by brout_m on 16/06/17.
//

#ifndef CPP_INDIE_STUDIO_DIM_HPP
#define CPP_INDIE_STUDIO_DIM_HPP

namespace resizer
{
  struct Dim
  {
    Dim();
    Dim(float x, float y, float width, float height, float pWidth,
        float pHeight);
    Dim(Dim const &);
    Dim &operator=(Dim const &);

    float m_x;
    float m_y;
    float m_width;
    float m_height;
  };

  typedef Dim Dimension;
}

#endif // CPP_INDIE_STUDIO_DIM_HPP
