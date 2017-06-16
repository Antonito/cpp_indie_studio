#include "pakpak_stdafx.hpp"

namespace game
{
  ContextGame::ContextGame(Ogre::RenderWindow *win, core::InputListener *input,
                           core::SettingsPlayer &settings)
      : core::AContext(win, input), m_game(), m_players(),
        m_settings(settings), m_quit(false), m_hud(nullptr)
  {
  }

  ContextGame::~ContextGame()
  {
  }

  void ContextGame::enable()
  {
    Pauser::unpause();
    m_input->setMouseEventCallback(this);
    m_input->setKeyboardEventCallback(this);
    m_quit = false;

    std::size_t nbPlayer = 6;

    m_game.setPlayerNb(0);
    m_game.setPlayerNb(nbPlayer);

    std::size_t nbLocalPlayer = 1;

    for (std::size_t i = 0; i < nbPlayer; ++i)
      {
	m_game[i].setCar(std::make_unique<EmptyCar>(m_game.sceneMgr(),
	                                            Ogre::Vector3(0, 0, 0),
	                                            Ogre::Vector3(0, 0, -1)));
      }
    if (m_players.size() < 2)
      {
	nope::log::Log(Debug) << "Creating HUD";
	m_hud = std::make_unique<core::HUD>();
      }

    for (std::size_t i = 0; i < nbLocalPlayer; ++i)
      {
	m_players.emplace_back(std::make_unique<LocalPlayer>(
	    m_win, m_game, &m_game[i], i, m_settings, m_hud.get(), *this));
      }
    updateViewPort();
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
  }

  core::GameState ContextGame::update()
  {
    m_input->capture();
    m_game.update();
    m_quit = m_hud->getQuit();
    return (m_quit ? core::GameState::Menu : core::GameState::InGame);
  }

  void ContextGame::display()
  {
  }

  bool ContextGame::keyPressed(OIS::KeyEvent const &ke)
  {
    std::size_t i = 0;
    for (std::unique_ptr<LocalPlayer> &p : m_players)
      {
	p->keyPressed(ke);
	++i;
      }
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

  void ContextGame::setQuit(bool quit)
  {
    m_quit = quit;
  }
}
