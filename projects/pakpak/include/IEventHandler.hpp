#ifndef IEVENTHANDLER_HPP_
#define IEVENTHANDLER_HPP_

#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>

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

#endif // !IEVENTHANDLER_HPP_