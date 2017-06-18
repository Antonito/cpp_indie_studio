#ifndef IEVENTHANDLER_HPP_
#define IEVENTHANDLER_HPP_

#if defined __APPLE__
#include <ois/OISMouse.h>
#include <ois/OISKeyboard.h>
#else
#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>
#endif

// Disable clang warning for vtable
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

namespace game
{
  class IEventHandler
  {
  public:
    virtual ~IEventHandler()
    {
    }
    virtual bool keyPressed(OIS::KeyEvent const &ke) = 0;
    virtual bool keyReleased(OIS::KeyEvent const &ke) = 0;

    virtual bool mouseMoved(OIS::MouseEvent const &me) = 0;
    virtual bool mousePressed(OIS::MouseEvent const &me,
                              OIS::MouseButtonID     id) = 0;
    virtual bool mouseReleased(OIS::MouseEvent const &me,
                               OIS::MouseButtonID     id) = 0;
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !IEVENTHANDLER_HPP_
