#include "ContextMenu.hpp"
#include "InputListener.hpp"
#include "GameState.hpp"

namespace menu
{
  ContextMenu::ContextMenu(Ogre::RenderWindow *win, core::InputListener *input)
      : core::AContext(win, input)
  {
  }

  ContextMenu::ContextMenu(ContextMenu const &that) : core::AContext(that)
  {
  }

  ContextMenu::ContextMenu(ContextMenu &&that)
      : core::AContext(std::move(that))
  {
  }

  ContextMenu::~ContextMenu()
  {
  }

  ContextMenu &ContextMenu::operator=(ContextMenu const &that)
  {
    if (this == &that)
      return (*this);
    core::AContext::operator=(that);
    return (*this);
  }

  ContextMenu &ContextMenu::operator=(ContextMenu &&that)
  {
    if (this == &that)
      return (*this);
    core::AContext::operator=(std::move(that));
    return (*this);
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
