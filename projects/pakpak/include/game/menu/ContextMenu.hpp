#ifndef CONTEXTMENU_HPP_
#define CONTEXTMENU_HPP_

#include <array>
#include "AContext.hpp"
#include "GUI.hpp"
#include "IMenuLayer.hpp"
#include "FastStack.hpp"
#include "MainMenu.hpp"
#include "GameState.hpp"
#include "MenuManager.hpp"

// Forward declaration for faster compilation
namespace Ogre
{
  class RenderWindow;
  class Viewport;
}

namespace menu
{
  class ContextMenu final : public core::AContext,
                            public OIS::KeyListener,
                            public OIS::MouseListener
  {
  public:
    ContextMenu(Ogre::RenderWindow *win, core::InputListener *input,
                core::SettingsPlayer &settings, core::NetworkManager &net);
    ContextMenu(ContextMenu const &) = delete;
    ContextMenu(ContextMenu &&) = delete;
    virtual ~ContextMenu();
    ContextMenu &operator=(ContextMenu const &) = delete;
    ContextMenu &operator=(ContextMenu &&) = delete;

    virtual void            enable();
    virtual void            disable();
    virtual core::GameState update();
    virtual void            display();
    bool keyPressed(const OIS::KeyEvent &arg);
    bool keyReleased(const OIS::KeyEvent &arg);
    bool mouseMoved(const OIS::MouseEvent &arg);
    bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

  private:
    MenuManager m_menu;
  };
}

#endif // !CONTEXTMENU_HPP_
