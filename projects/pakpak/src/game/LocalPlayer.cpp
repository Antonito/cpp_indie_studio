#include "pakpak_stdafx.hpp"

namespace game
{
  LocalPlayer::LocalPlayer(Ogre::RenderWindow *win, GameData &g,
                           std::vector<PlayerData> &p, int playerIndex,
                           int order, core::SettingsPlayer &settings,
                           core::HUD *hud, game::ContextGame &contextGame,
                           std::vector<std::unique_ptr<LocalPlayer>> &players,
                           std::uint8_t nbplayers, std::uint16_t id,
                           core::SoundManager &sound)
      : m_data(p), m_playerIndex(playerIndex), m_cameraMode(CameraMode::Top),
        m_layers(), m_currentLayers(), m_cam(nullptr), m_viewport(nullptr),
        m_rounds(), m_settings(settings), m_actions(), m_win(win),
        m_order(order), m_hud(hud), m_contextGame(contextGame), m_id(id),
        m_sound(sound)
  {
    m_layers[static_cast<std::size_t>(GameLayer::Loading)] =
        std::make_unique<Loading>(g, *this, hud, players);
    m_layers[static_cast<std::size_t>(GameLayer::PreGame)] =
        std::make_unique<PreGame>(g, *this, hud, players);
    switch (nbplayers)
      {
      case (2):
	m_layers[static_cast<std::size_t>(GameLayer::InGame)] =
	    std::make_unique<InGame<2>>(g, *this, hud, players);
	break;
      case (3):
	m_layers[static_cast<std::size_t>(GameLayer::InGame)] =
	    std::make_unique<InGame<3>>(g, *this, hud, players);
	break;
      case (4):
	m_layers[static_cast<std::size_t>(GameLayer::InGame)] =
	    std::make_unique<InGame<4>>(g, *this, hud, players);
	break;
      default:
	m_layers[static_cast<std::size_t>(GameLayer::InGame)] =
	    std::make_unique<InGame<1>>(g, *this, hud, players);
      }
    m_layers[static_cast<std::size_t>(GameLayer::GameGUI)] =
        std::make_unique<GameGUI>(g, *this, hud, players);
    m_layers[static_cast<std::size_t>(GameLayer::Spectator)] =
        std::make_unique<Spectator>(g, *this, hud, players);
    m_layers[static_cast<std::size_t>(GameLayer::SpecGUI)] =
        std::make_unique<SpecGUI>(g, *this, hud, players);
    m_layers[static_cast<std::size_t>(GameLayer::PostGame)] =
        std::make_unique<PostGame>(g, *this, hud, players);
    m_layers[static_cast<std::size_t>(GameLayer::Score)] =
        std::make_unique<Score>(g, *this, hud, players);
    m_layers[static_cast<std::size_t>(GameLayer::Chat)] =
        std::make_unique<Chat>(g, *this, hud, players);
    m_layers[static_cast<std::size_t>(GameLayer::Menu)] =
        std::make_unique<Menu>(g, *this, hud, players);

    m_currentLayers.push(m_layers[static_cast<std::size_t>(GameLayer::InGame)]
                             .get()); // TODO: insert LOADING instead
    m_currentLayers.top()->enable();
    m_cam = m_data[static_cast<std::size_t>(m_playerIndex)].car().getCamera();
    m_cam->setNearClipDistance(3);

    Log(nope::log::Debug) << "Adding viewport '" << m_order << "' to window";
    m_viewport = m_win->addViewport(m_cam, m_order);
    m_viewport->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 0.0f));
    m_cam->setAspectRatio(Ogre::Real(m_viewport->getActualWidth()) /
                          Ogre::Real(m_viewport->getActualHeight()));
    setActionMap();
  }

  LocalPlayer::LocalPlayer(LocalPlayer &&that)
      : m_data(that.m_data), m_cameraMode(std::move(that.m_cameraMode)),
        m_layers(std::move(that.m_layers)),
        m_currentLayers(std::move(that.m_currentLayers)), m_cam(that.m_cam),
        m_viewport(that.m_viewport), m_rounds(that.m_rounds),
        m_settings(that.m_settings), m_actions(that.m_actions),
        m_win(that.m_win), m_order(that.m_order), m_hud(that.m_hud),
        m_contextGame(that.m_contextGame), m_id(that.m_id),
        m_sound(that.m_sound)
  {
    that.m_cam = nullptr;
    that.m_viewport = nullptr;
    that.m_win = nullptr;
    that.m_hud = nullptr;
    that.m_order = 0;
  }

  LocalPlayer::~LocalPlayer()
  {
    Log(nope::log::Debug) << "Removing viewport '" << m_order
                          << "' from window";
    m_win->removeViewport(m_order);
  }

  void LocalPlayer::setViewPort(Ogre::Real left, Ogre::Real top,
                                Ogre::Real width, Ogre::Real height)
  {
    m_viewport->setDimensions(left, top, width, height);
    m_cam->setAspectRatio(Ogre::Real(m_viewport->getActualWidth()) /
                          Ogre::Real(m_viewport->getActualHeight()));
  }

  void LocalPlayer::crossFinishLine(
      std::chrono::time_point<std::chrono::high_resolution_clock> finishTime,
      int                                                         nbRounds)
  {
    static int currentRound = 0;

    if (currentRound < nbRounds)
      {
	currentRound++;
	m_rounds.push_back(finishTime);
      }
  }

  bool LocalPlayer::keyPressed(OIS::KeyEvent const &ke)
  {
    for (std::size_t i = m_currentLayers.size(); i > 0; --i)
      {
	if (m_currentLayers[i - 1]->keyPressed(ke))
	  {
	    return (true);
	  }
      }
    return (false);
  }

  bool LocalPlayer::keyReleased(OIS::KeyEvent const &ke)
  {
    for (std::size_t i = m_currentLayers.size(); i > 0; --i)
      {
	if (m_currentLayers[i - 1]->keyReleased(ke))
	  {
	    return (true);
	  }
      }
    return (false);
  }

  bool LocalPlayer::mouseMoved(OIS::MouseEvent const &me)
  {
    for (std::size_t i = m_currentLayers.size(); i > 0; --i)
      {
	if (m_currentLayers[i - 1]->mouseMoved(me))
	  {
	    return (true);
	  }
      }
    return (false);
  }

  bool LocalPlayer::mousePressed(OIS::MouseEvent const &me,
                                 OIS::MouseButtonID     id)
  {
    for (std::size_t i = m_currentLayers.size(); i > 0; --i)
      {
	if (m_currentLayers[i - 1]->mousePressed(me, id))
	  {
	    return (true);
	  }
      }
    return (false);
  }

  bool LocalPlayer::mouseReleased(OIS::MouseEvent const &me,
                                  OIS::MouseButtonID     id)
  {
    for (std::size_t i = m_currentLayers.size(); i > 0; --i)
      {
	if (m_currentLayers[i - 1]->mouseReleased(me, id))
	  {
	    return (true);
	  }
      }
    return (false);
  }

  void LocalPlayer::push(GameLayer layer)
  {
    m_currentLayers.push(m_layers[static_cast<std::size_t>(layer)].get());
  }

  void LocalPlayer::popLayer()
  {
    m_currentLayers.top()->disable();
    m_currentLayers.pop();
  }

  ACar &LocalPlayer::car()
  {
    return (m_data[static_cast<std::size_t>(m_playerIndex)].car());
  }

  ACar const &LocalPlayer::car() const
  {
    return (m_data[static_cast<std::size_t>(m_playerIndex)].car());
  }

  core::SettingsPlayer &LocalPlayer::settings()
  {
    return (m_settings);
  }

  void LocalPlayer::setActionMap()
  {
    m_actions.emplace(
        "speedUp",
        std::make_pair(&LocalPlayer::speedUp, &LocalPlayer::speedUpReleased));
    m_actions.emplace("slowDown",
                      std::make_pair(&LocalPlayer::slowDown,
                                     &LocalPlayer::slowDownReleased));
    m_actions.emplace("turnLeft",
                      std::make_pair(&LocalPlayer::turnLeft,
                                     &LocalPlayer::turnLeftReleased));
    m_actions.emplace("turnRight",
                      std::make_pair(&LocalPlayer::turnRight,
                                     &LocalPlayer::turnRightReleased));
    m_actions.emplace("useObject",
                      std::make_pair(&LocalPlayer::useObject,
                                     &LocalPlayer::useObjectReleased));
    m_actions.emplace("changeView",
                      std::make_pair(&LocalPlayer::changeView,
                                     &LocalPlayer::changeViewReleased));
    m_actions.emplace("displayMap",
                      std::make_pair(&LocalPlayer::displayMap,
                                     &LocalPlayer::displayMapReleased));
    m_actions.emplace("openChat",
                      std::make_pair(&LocalPlayer::openChat,
                                     &LocalPlayer::openChatReleased));
    m_actions.emplace("openMenu",
                      std::make_pair(&LocalPlayer::openMenu,
                                     &LocalPlayer::openMenuReleased));
  }

  std::pair<void (LocalPlayer::*)(), void (LocalPlayer::*)()> &
      LocalPlayer::actions(std::string const &action)
  {
    nope::log::Log(Debug) << "Player '" << m_order << "' action '" << action
                          << "'";
    return (m_actions[action]);
  }

  void LocalPlayer::speedUp()
  {
    nope::log::Log(Debug) << "ACC mode !!";
    m_sound.stopSound(core::ESound::IDLE_KART_SOUND);
    m_sound.playSound(core::ESound::ACC_KART_SOUND);
    m_sound.loopSound(core::ESound::ACC_KART_SOUND);
    m_sound.setVolumeSource(core::ESound::ACC_KART_SOUND,
                            0.45f * m_sound.getVolume());

    m_data[static_cast<std::size_t>(m_playerIndex)].car().move(-1);
  }

  void LocalPlayer::slowDown()
  {
    m_sound.stopSound(core::ESound::ACC_KART_SOUND);
    if (m_data[static_cast<std::size_t>(m_playerIndex)].car().speed() >= 5.0)
      {
	m_sound.stopSound(core::ESound::IDLE_KART_SOUND);
	m_sound.playSound(core::ESound::SLOW_KART_SOUND);
	m_sound.setVolumeSource(core::ESound::SLOW_KART_SOUND,
	                        0.45f * m_sound.getVolume());
      }
    m_data[static_cast<std::size_t>(m_playerIndex)].car().move(1);
  }

  void LocalPlayer::turnLeft()
  {
    m_data[static_cast<std::size_t>(m_playerIndex)].car().turn(1);
  }

  void LocalPlayer::turnRight()
  {
    m_data[static_cast<std::size_t>(m_playerIndex)].car().turn(-1);
  }

  void LocalPlayer::useObject()
  {
    // TODO: implement Bonus Object
  }

  void LocalPlayer::changeView()
  {
  }

  void LocalPlayer::displayMap()
  {
    // TODO: implement MiniMap
  }

  void LocalPlayer::openChat()
  {
    m_currentLayers.push(
        m_layers[static_cast<std::size_t>(GameLayer::Chat)].get());
  }

  void LocalPlayer::openMenu()
  {
    if (m_layers[static_cast<std::size_t>(GameLayer::Menu)].get() !=
        m_currentLayers.top())
      {
	if (!Pauser::isPaused())
	  {
	    nope::log::Log(Debug) << "Opening Pause Menu";
	    m_currentLayers.push(
	        m_layers[static_cast<std::size_t>(GameLayer::Menu)].get());
	    m_currentLayers.top()->enable();
	  }
	else
	  {
	    Pauser::unpause();
	  }
      }
  }

  void LocalPlayer::speedUpReleased()
  {
    nope::log::Log(Debug) << "Idle mode !!";
    double rawSpeed =
        m_data[static_cast<std::size_t>(m_playerIndex)].car().speed();
    std::uint32_t speed =
        static_cast<std::uint32_t>((rawSpeed > 0 ? rawSpeed : -rawSpeed) / 50);

    m_sound.stopSound(core::ESound::ACC_KART_SOUND);
    if (speed > 30)
      {
	nope::log::Log(Debug) << "SLow mode !!";
	m_sound.playSound(core::ESound::SLOW_KART_SOUND);
	m_sound.setVolumeSource(core::ESound::SLOW_KART_SOUND,
	                        0.45f * m_sound.getVolume());
      }
    m_sound.playSound(core::ESound::IDLE_KART_SOUND);
    m_sound.loopSound(core::ESound::IDLE_KART_SOUND);
    m_sound.setVolumeSource(core::ESound::IDLE_KART_SOUND,
                            2.0f * m_sound.getVolume());
    m_data[static_cast<std::size_t>(m_playerIndex)].car().move(0);
  }

  void LocalPlayer::slowDownReleased()
  {
    m_sound.playSound(core::ESound::IDLE_KART_SOUND);
    m_sound.loopSound(core::ESound::IDLE_KART_SOUND);
    m_sound.setVolumeSource(core::ESound::IDLE_KART_SOUND,
                            2.0f * m_sound.getVolume());
    m_data[static_cast<std::size_t>(m_playerIndex)].car().move(0);
  }

  void LocalPlayer::turnLeftReleased()
  {
    m_data[static_cast<std::size_t>(m_playerIndex)].car().turn(0);
  }

  void LocalPlayer::turnRightReleased()
  {
    m_data[static_cast<std::size_t>(m_playerIndex)].car().turn(0);
  }

  void LocalPlayer::useObjectReleased()
  {
  }

  void LocalPlayer::changeViewReleased()
  {
  }

  void LocalPlayer::displayMapReleased()
  {
  }

  void LocalPlayer::openChatReleased()
  {
  }

  void LocalPlayer::openMenuReleased()
  {
  }

  int LocalPlayer::order() const
  {
    return (m_order);
  }

  void LocalPlayer::order(int order)
  {
    m_order = order;
  }

  void LocalPlayer::display()
  {
    for (std::uint32_t i = 0; i < m_layers.size(); ++i)
      {
	m_layers[i]->display();
      }
  }

  std::uint16_t LocalPlayer::getID() const
  {
    return m_id;
  }

  void LocalPlayer::setID(std::uint16_t id)
  {
    m_id = id;
  }

  bool LocalPlayer::operator==(std::uint16_t id) const
  {
    return m_id == id;
  }

  std::size_t LocalPlayer::getRank() const
  {
    return (m_data[static_cast<std::size_t>(m_playerIndex)].getRank());
  }

  bool LocalPlayer::getFinished() const
  {
    return (m_data[static_cast<std::size_t>(m_playerIndex)].getFinished());
  }
}
