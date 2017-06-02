//
// Created by duhieu_b on 23/05/17.
//

#ifndef CPP_INDIE_STUDIO_IMENULAYER_HPP_
#define CPP_INDIE_STUDIO_IMENULAYER_HPP_

#include <CEGUI/CEGUI.h>
#include <OIS/OIS.h>
#include <iostream>
#include "GameState.hpp"

namespace core
{
  class IMenuLayer
  {
  public:
    virtual ~IMenuLayer()
    {
    }

    virtual void draw() = 0;
    virtual void entry() = 0;
    virtual void exit() = 0;
    virtual void destroy() = 0;
    virtual GameState update() const = 0;
    virtual void build() = 0;
    virtual bool keyPressed(const OIS::KeyEvent &arg) = 0;
    virtual bool mouseMoved(const OIS::MouseEvent &arg) = 0;
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;
    virtual bool keyReleased(const OIS::KeyEvent &arg) = 0;
  };
}

#endif // CPP_INDIE_STUDIO_IMENULAYER_HPP_
