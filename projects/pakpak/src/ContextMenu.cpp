#include "pakpak_stdafx.hpp"

namespace menu
{
  ContextMenu::ContextMenu(Ogre::RenderWindow *win, core::InputListener *input)
      : core::AContext(win, input), m_viewport(nullptr), m_camera(nullptr), m_gui({})
  {
  }

  ContextMenu::~ContextMenu()
  {
  }

  void ContextMenu::enable()
  {
    // m_win->addViewport();
  }

  void ContextMenu::disable()
  {
  }

  core::GameState ContextMenu::update()
  {
    return (core::GameState::Menu);
  }

  void ContextMenu::display()
  {
  }
}
