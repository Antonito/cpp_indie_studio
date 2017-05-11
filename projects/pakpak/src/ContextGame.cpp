#include <OgreRenderWindow.h>
#include "InputListener.hpp"
#include "GameState.hpp"
#include "ContextGame.hpp"

namespace game
{
  ContextGame::ContextGame(Ogre::RenderWindow *win, core::InputListener *input)
      : core::AContext(win, input)
  {
  }

  ContextGame::ContextGame(ContextGame const &that) : core::AContext(that)
  {
  }

  ContextGame::ContextGame(ContextGame &&that)
      : core::AContext(std::move(that))
  {
  }

  ContextGame::~ContextGame()
  {
  }

  ContextGame &ContextGame::operator=(ContextGame const &that)
  {
    if (this == &that)
      return (*this);
    core::AContext::operator=(that);
    return (*this);
  }

  ContextGame &ContextGame::operator=(ContextGame &&that)
  {
    if (this == &that)
      return (*this);
    core::AContext::operator=(std::move(that));
    return (*this);
  }

  void ContextGame::enable()
  {
    // m_win->addViewport()
  }

  void ContextGame::disable()
  {
  }

  core::GameState ContextGame::update()
  {
    return (core::GameState::InGame);
  }

  void ContextGame::display()
  {
  }
}