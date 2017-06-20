#include "pakpak_stdafx.hpp"

namespace game
{
  ContextGame::ContextGame(Ogre::RenderWindow *win, core::InputListener *input,
                           core::SettingsPlayer &settings,
                           core::NetworkManager &net,
                           core::SoundManager &  sound)
      : core::AContext(win, input), m_game(), m_players(),
        m_settings(settings), m_quit(false), m_hud(nullptr), m_net(net),
        m_sound(sound), m_timer(850), m_gameStart(false)
  {
  }

  ContextGame::~ContextGame()
  {
  }

  void ContextGame::enable()
  {
    nope::log::Log(Debug) << "Game context enabled";

    Pauser::unpause();
    m_input->setMouseEventCallback(this);
    m_input->setKeyboardEventCallback(this);
    m_quit = false;

    std::size_t nbPlayer = m_settings.getPlayerCount();

    m_game.setPlayerNb(nbPlayer);

    std::uint32_t nbLocalPlayer = m_settings.getPlayerCount();

    m_timer.start();
    for (std::size_t i = 0; i < nbPlayer; ++i)
      {
	m_game[i].setCar(std::make_unique<EmptyCar>(
	    m_game, Ogre::Vector3(0, 10, -100.0f * static_cast<float>(i)),
	    Ogre::Quaternion(Ogre::Degree(180), Ogre::Vector3::UNIT_Y)));
      }

    nope::log::Log(Debug) << "Creating HUD";
    m_hud = std::make_unique<core::HUD>();

    for (std::size_t i = 0; i < nbLocalPlayer; ++i)
      {
	m_players.emplace_back(std::make_unique<LocalPlayer>(
	    m_win, m_game, &m_game[i], static_cast<int>(i), m_settings,
	    i == 0 ? m_hud.get() : nullptr, *this, m_players, nbLocalPlayer,
	    m_sound));
      }
    /*for (std::size_t i = nbLocalPlayer; i < nbPlayer; ++i)
      {
	m_ia.emplace_back(
	    std::make_unique<Ai>(m_game[i].car(), m_game.map().getNodes()));
      }*/
    m_sound.playSound(core::ESound::GAME_SONG);
    m_sound.loopSound(core::ESound::GAME_SONG);
    m_sound.playSound(core::ESound::IDLE_KART_SOUND);
    m_sound.loopSound(core::ESound::IDLE_KART_SOUND);
    m_sound.setVolumeSource(core::ESound::IDLE_KART_SOUND,
                            2.0f * m_sound.getVolume());
    m_sound.setVolumeSource(core::ESound::GAME_SONG,
                            0.2f * m_sound.getVolume());
    updateViewPort();

    m_input->setPhysicWorld(m_game.physicWorld());
  }

  void ContextGame::updateViewPort()
  {
    int size = static_cast<int>(m_players.size());

    for (int i = 0; i < size; ++i)
      {
	m_players[static_cast<std::size_t>(i)]->setViewPort(
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
    nope::log::Log(Debug) << "Game context disabled";
    m_players.clear();
    m_gameStart = false;
    m_sound.stopSound(core::ESound::GAME_SONG);
    m_sound.stopSound(core::ESound::IDLE_KART_SOUND);
    m_input->setPhysicWorld(nullptr);
    nope::log::Log(Debug) << "Disabling game.";
    if (m_net.isConnected())
      {
	nope::log::Log(Debug) << "Game is connected to Game Server.";
	m_net.disconnect();
      }
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
    if (m_timer.reached() && !m_gameStart)
      {
	m_sound.playSound(core::ESound::START_SONG);
	m_sound.setVolumeSource(core::ESound::START_SONG,
	                        0.4f * m_sound.getVolume());
	m_gameStart = true;
      }

    for (std::uint8_t i = 0; i < m_players.size(); ++i)
      {
	/*m_sound.setPosition(core::ESound::ACC_KART_SOUND,
	                    m_players[i]->car().position().x,
	                    m_players[i]->car().position().y,
	                    m_players[i]->car().position().z);
          m_sound.setPosition(core::ESound::SLOW_KART_SOUND,
                              m_players[i]->car().position().x,
                              m_players[i]->car().position().y,
                              m_players[i]->car().position().z);
          m_sound.setPosition(core::ESound::BOOST_SONG,
                              m_players[i]->car().position().x,
                              m_players[i]->car().position().y,
                              m_players[i]->car().position().z);
          m_sound.setPosition(core::ESound::IDLE_KART_SOUND,
                              m_players[i]->car().position().x,
                              m_players[i]->car().position().y,
                              m_players[i]->car().position().z);
          m_sound.setPosition(core::ESound::KLAXON_KART_SOUND,
                              m_players[i]->car().position().x,
                              m_players[i]->car().position().y,
                              m_players[i]->car().position().z);*/
	m_players[i]->display();
      }
    /*for (std::unique_ptr<Ai> const &l_ia : m_ia)
      {
          m_sound.setPosition(core::ESound::ACC_KART_SOUND,
                              l_ia->car().position().x,
                              l_ia->car().position().y,
                              l_ia->car().position().z);
          m_sound.setPosition(core::ESound::SLOW_KART_SOUND,
                              l_ia->car().position().x,
                              l_ia->car().position().y,
                              l_ia->car().position().z);
          m_sound.setPosition(core::ESound::BOOST_SONG,
                              l_ia->car().position().x,
                              l_ia->car().position().y,
                              l_ia->car().position().z);
          m_sound.setPosition(core::ESound::IDLE_KART_SOUND,
                              l_ia->car().position().x,
                              l_ia->car().position().y,
                              l_ia->car().position().z);
          m_sound.setPosition(core::ESound::KLAXON_KART_SOUND,
                              l_ia->car().position().x,
                              l_ia->car().position().y,
                              l_ia->car().position().z);
          l_ia->race();
      }*/
  }

  bool ContextGame::keyPressed(OIS::KeyEvent const &ke)
  {
    std::size_t i = 0;
    for (std::unique_ptr<LocalPlayer> &p : m_players)
      {
	nope::log::Log(Debug) << "\t\tPressed for player " << i;
	p->keyPressed(ke);
	++i;
      }
    nope::log::Log(Debug) << "\n";
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
