#ifndef CONTEXTMENU_HPP_
#define CONTEXTMENU_HPP_

#if defined(_WIN32) && !defined(__on__linux__)
#include <OgreRenderWindow.h>
#endif

#if defined(__linux__)
#include <OGRE/OgreRenderWindow.h>
#endif

#include "AContext.hpp"

// class Ogre::RenderWindow;
namespace menu
{
  class ContextMenu final : public core::AContext
  {
  public:
    ContextMenu(Ogre::RenderWindow *win, core::InputListener *input);
    ContextMenu(ContextMenu const &);
    ContextMenu(ContextMenu &&);
    virtual ~ContextMenu();

    ContextMenu &operator=(ContextMenu const &);
    ContextMenu &operator=(ContextMenu &&);

    virtual void enable();
    virtual void disable();

    virtual core::GameState update();
    virtual void            display();

  private:
  };
}

#endif // !CONTEXTMENU_HPP_
