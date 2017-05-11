#ifndef CONTEXTMENU_HPP_
#define CONTEXTMENU_HPP_

#include "AContext.hpp"

// Forward declaration for faster compilation
namespace Ogre
{
  class RenderWindow;
}

namespace menu
{
  class ContextMenu final : public core::AContext
  {
  public:
    ContextMenu(Ogre::RenderWindow *win, core::InputListener *input);
    ContextMenu(ContextMenu const &) = delete;
    ContextMenu(ContextMenu &&) = delete;
    virtual ~ContextMenu();

    ContextMenu &operator=(ContextMenu const &) = delete;
    ContextMenu &operator=(ContextMenu &&) = delete;

    virtual void enable();
    virtual void disable();

    virtual core::GameState update();
    virtual void            display();

  private:
  };
}

#endif // !CONTEXTMENU_HPP_
