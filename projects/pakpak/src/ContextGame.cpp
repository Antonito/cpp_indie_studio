#include <OGRE/OgreRenderWindow.h>
#include "InputListener.hpp"
#include "GameState.hpp"
#include "ContextGame.hpp"

namespace game
{
  ContextGame::ContextGame(Ogre::RenderWindow *win, core::InputListener *input)
      : core::AContext(win, input)
  {
  }

  ContextGame::~ContextGame()
  {
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