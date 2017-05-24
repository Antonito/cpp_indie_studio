#ifndef CONTEXTMENU_HPP_
#define CONTEXTMENU_HPP_

#include "AContext.hpp"
#include "GUI.hpp"
#include "IMenuLayer.hpp"
#include "FastStack.hpp"

// Forward declaration for faster compilation
namespace Ogre
{
  class RenderWindow;
  class Viewport;
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
    Ogre::Viewport *                    m_viewport;
    Ogre::Camera *                      m_camera;
    core::FastStack<core::IMenuLayer *> m_gui;
  };
}

#endif // !CONTEXTMENU_HPP_
