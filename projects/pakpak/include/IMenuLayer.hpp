//
// Created by duhieu_b on 23/05/17.
//

#ifndef CPP_INDIE_STUDIO_IMENULAYER_HPP_
#define CPP_INDIE_STUDIO_IMENULAYER_HPP_

//#include <CEGUI/cegui.h>
#include <iostream>
#include <glm>
#include "GameState.hpp"

namespace core
{
  class IMenuLayer
  {
  public:
    virtual ~IMenuLayer() {}

    virtual core::GameState changeScreen() const = 0;

    virtual void draw() = 0;

    virtual void entry() = 0;

    virtual void exit() = 0;

    virtual void destroy() = 0;

    virtual void update() = 0;

    virtual void build() = 0;
  };
}

#endif // CPP_INDIE_STUDIO_IMENULAYER_HPP_
