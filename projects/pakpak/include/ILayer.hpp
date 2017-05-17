#ifndef ILAYER_HPP_
#define ILAYER_HPP_

#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>

namespace game
{
  class ILayer
  {
  public:
    virtual ~ILayer()
    {
    }

    virtual void enable() = 0;
    virtual void disable() = 0;

    virtual void update() = 0;
    virtual void display() = 0;

    // Event handlers, return true if handled
    virtual bool keyPressed(OIS::KeyEvent const &ke) = 0;
    virtual bool keyReleased(OIS::KeyEvent const &ke) = 0;

    virtual bool mouseMoved(OIS::MouseEvent const &me) = 0;
    virtual bool mousePressed(OIS::MouseEvent const &me,
                              OIS::MouseButtonID     id) = 0;
    virtual bool mouseReleased(OIS::MouseEvent const &me,
                               OIS::MouseButtonID     id) = 0;
  };
}

#endif // !ILAYER_HPP_
