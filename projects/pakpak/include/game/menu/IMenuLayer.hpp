//
// Created by duhieu_b on 23/05/17.
//

#ifndef CPP_INDIE_STUDIO_IMENULAYER_HPP_
#define CPP_INDIE_STUDIO_IMENULAYER_HPP_

#include <CEGUI/CEGUI.h>
#if defined __APPLE__
#include <ois/OIS.h>
#else
#include <OIS/OIS.h>
#endif
#include <iostream>
#include "GameState.hpp"

// Disable clang warning for vtable
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

namespace core
{
  class IMenuLayer
  {
  public:
    virtual ~IMenuLayer()
    {
    }

    virtual void      draw() = 0;
    virtual void      entry() = 0;
    virtual void      exit() = 0;
    virtual void      destroy() = 0;
    virtual GameState update() const = 0;
    virtual void      build() = 0;
    virtual bool keyPressed(const OIS::KeyEvent &arg) = 0;
    virtual bool mouseMoved(const OIS::MouseEvent &arg) = 0;
    virtual bool mousePressed(const OIS::MouseEvent &arg,
                              OIS::MouseButtonID     id) = 0;
    virtual bool mouseReleased(const OIS::MouseEvent &arg,
                               OIS::MouseButtonID     id) = 0;
    virtual bool keyReleased(const OIS::KeyEvent &arg) = 0;
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // CPP_INDIE_STUDIO_IMENULAYER_HPP_
