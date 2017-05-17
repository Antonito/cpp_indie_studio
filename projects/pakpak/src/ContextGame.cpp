#include "pakpak_stdafx.hpp"

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

  bool ContextGame::keyPressed(OIS::KeyEvent const &ke)
  {
    for (LocalPlayer &p : m_players)
      {
	p.keyPressed(ke);
      }
    return (true);
  }

  bool ContextGame::keyReleased(OIS::KeyEvent const &ke)
  {
    for (LocalPlayer &p : m_players)
      {
	p.keyReleased(ke);
      }
    return (true);
  }

  bool ContextGame::mouseMoved(OIS::MouseEvent const &me)
  {
    for (LocalPlayer &p : m_players)
      {
	p.mouseMoved(me);
      }
    return (true);
  }

  bool ContextGame::mousePressed(OIS::MouseEvent const &me,
                                 OIS::MouseButtonID     id)
  {
    for (LocalPlayer &p : m_players)
      {
	p.mousePressed(me, id);
      }
    return (true);
  }

  bool ContextGame::mouseReleased(OIS::MouseEvent const &me,
                                  OIS::MouseButtonID     id)
  {
    for (LocalPlayer &p : m_players)
      {
	p.mouseReleased(me, id);
      }
    return (true);
  }
}
