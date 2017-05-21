#include "pakpak_stdafx.hpp"

namespace game
{
  ContextGame::ContextGame(Ogre::RenderWindow *win, core::InputListener *input)
      : core::AContext(win, input), m_game(), m_players()
  {
  }

  ContextGame::~ContextGame()
  {
  }

  void ContextGame::enable()
  {
    m_input->setMouseEventCallback(this);
    m_input->setKeyboardEventCallback(this);

    std::int32_t nbPlayer = 1;

    m_game.setPlayerNb(nbPlayer);

    for (std::int32_t i = 0; i < nbPlayer; ++i)
      {
	m_game[i].setCar(std::make_unique<EmptyCar>(m_game.sceneMgr(),
	                                            Ogre::Vector3(0, 0, 0),
	                                            Ogre::Vector3(0, 0, -1)));
	m_players.emplace_back(m_win, m_game, m_game[i]);
      }
  }

  void ContextGame::disable()
  {
    m_players.clear();
  }

  core::GameState ContextGame::update()
  {
    m_input->capture();
    m_game.update();
    return (core::GameState::InGame);
  }

  void ContextGame::display()
  {
  }

  bool ContextGame::keyPressed(OIS::KeyEvent const &ke)
  {
    if (ke.key == OIS::KC_ESCAPE)
      {
	m_input->shutdown();
      }

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
