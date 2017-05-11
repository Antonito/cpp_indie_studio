#include "ContextMenu.hpp"
#include "InputListener.hpp"
#include "GameState.hpp"

namespace menu
{
  ContextMenu::ContextMenu(Ogre::RenderWindow *win, core::InputListener *input)
      : core::AContext(win, input)
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
