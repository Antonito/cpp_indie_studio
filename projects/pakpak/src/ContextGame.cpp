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

    std::size_t nbPlayer = 1;

    m_game.setPlayerNb(nbPlayer);

    std::size_t nbLocalPlayer = 1;

    for (std::size_t i = 0; i < nbPlayer; ++i)
      {
	m_game[i].setCar(std::make_unique<EmptyCar>(
	    m_game, Ogre::Vector3(0, 0, 0), Ogre::Vector3(0, 0, -1)));
      }

    for (std::size_t i = 0; i < nbLocalPlayer; ++i)
      {
	m_players.emplace_back(
	    std::make_unique<LocalPlayer>(m_win, m_game, &m_game[i], i));
      }

    updateViewPort();

    m_input->setPhysicWorld(m_game.physicWorld());
  }

  void ContextGame::updateViewPort()
  {

    int size = static_cast<int>(m_players.size());

    for (std::size_t i = 0; i < static_cast<std::size_t>(size); ++i)
      {
	m_players[i]->setViewPort(
	    static_cast<Ogre::Real>(
	        static_cast<double>((i % 2) * ((size - 1) / 2)) * 0.5),
	    static_cast<Ogre::Real>(
	        static_cast<double>(
	            (((size - 1) / 2) * i / 2 + (1 - (size - 1) / 2) * i)) *
	        0.5),
	    static_cast<Ogre::Real>(
	        1 -
	        0.5 * static_cast<double>((((size - 1) / 2) * (1 - (i / 2)) +
	                                   (i / 2) * (size / 4)))),
	    static_cast<Ogre::Real>(
	        1 - 0.5 * static_cast<double>((size + 1) / 3)));
      }
  }

  void ContextGame::disable()
  {
    m_players.clear();
    m_input->setPhysicWorld(nullptr);
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

    std::size_t i = 0;
    for (std::unique_ptr<LocalPlayer> &p : m_players)
      {
	std::cout << "		Pressed for player " << i << std::endl;

	p->keyPressed(ke);
	++i;
      }
    std::cout << std::endl;
    return (true);
  }

  bool ContextGame::keyReleased(OIS::KeyEvent const &ke)
  {
    for (std::unique_ptr<LocalPlayer> &p : m_players)
      {
	p->keyReleased(ke);
      }
    return (true);
  }

  bool ContextGame::mouseMoved(OIS::MouseEvent const &me)
  {
    for (std::unique_ptr<LocalPlayer> &p : m_players)
      {
	p->mouseMoved(me);
      }
    return (true);
  }

  bool ContextGame::mousePressed(OIS::MouseEvent const &me,
                                 OIS::MouseButtonID     id)
  {
    for (std::unique_ptr<LocalPlayer> &p : m_players)
      {
	p->mousePressed(me, id);
      }
    return (true);
  }

  bool ContextGame::mouseReleased(OIS::MouseEvent const &me,
                                  OIS::MouseButtonID     id)
  {
    for (std::unique_ptr<LocalPlayer> &p : m_players)
      {
	p->mouseReleased(me, id);
      }
    return (true);
  }
}
