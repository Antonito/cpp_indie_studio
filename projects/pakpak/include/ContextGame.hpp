#ifndef CONTEXTGAME_HPP_
#define CONTEXTGAME_HPP_

#if defined(_WIN32) && !defined(__on__linux__)
#include <OgreRenderWindow.h>
#endif

#if defined(__linux__)
#include <OGRE/OgreRenderWindow.h>
#endif

#include "AContext.hpp"

//  class Ogre::RenderWindow;

namespace game
{
  class ContextGame final : public core::AContext
  {
  public:
    ContextGame(Ogre::RenderWindow *win, core::InputListener *input);
    ContextGame(ContextGame const &) = delete;
    ContextGame(ContextGame &&) = delete;
    virtual ~ContextGame();

    ContextGame &operator=(ContextGame const &) = delete;
    ContextGame &operator=(ContextGame &&) = delete;

    virtual void enable();
    virtual void disable();

    virtual core::GameState update();
    virtual void            display();

  private:
  };
}

#endif // !CONTEXTGAME_HPP_
