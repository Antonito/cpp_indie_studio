#include "pakpak_stdafx.hpp"
#include "Logger.hpp"

namespace game
{
  LocalPlayer::LocalPlayer(Ogre::RenderWindow *win, GameData &g, PlayerData *p,
                           int order, core::SettingsPlayer &settings)
      : m_data(p), m_cameraMode(CameraMode::Top), m_layers(),
        m_currentLayers(), m_cam(nullptr), m_viewport(nullptr), m_rounds(),
        m_settings(settings), m_actions(), m_win(win), m_order(order)
  {
    m_layers[static_cast<std::size_t>(GameLayer::Loading)] =
        std::make_unique<Loading>(g, *this);
    m_layers[static_cast<std::size_t>(GameLayer::PreGame)] =
        std::make_unique<PreGame>(g, *this);
    m_layers[static_cast<std::size_t>(GameLayer::InGame)] =
        std::make_unique<InGame>(g, *this);
    m_layers[static_cast<std::size_t>(GameLayer::GameGUI)] =
        std::make_unique<GameGUI>(g, *this);
    m_layers[static_cast<std::size_t>(GameLayer::Spectator)] =
        std::make_unique<Spectator>(g, *this);
    m_layers[static_cast<std::size_t>(GameLayer::SpecGUI)] =
        std::make_unique<SpecGUI>(g, *this);
    m_layers[static_cast<std::size_t>(GameLayer::PostGame)] =
        std::make_unique<PostGame>(g, *this);
    m_layers[static_cast<std::size_t>(GameLayer::Score)] =
        std::make_unique<Score>(g, *this);
    m_layers[static_cast<std::size_t>(GameLayer::Chat)] =
        std::make_unique<Chat>(g, *this);
    m_layers[static_cast<std::size_t>(GameLayer::Menu)] =
        std::make_unique<Menu>(g, *this);

    m_currentLayers.push(m_layers[static_cast<std::size_t>(GameLayer::InGame)]
                             .get()); // TODO: insert LOADING instead

    m_cam = m_data->car().getCamera();
    // m_cam = g.createCamera("PlayerCam"); // todo: name
    // m_cam->setPosition(m_car->position() - m_car->direction());
    m_cam->lookAt(Ogre::Vector3(0, 0, 0));
    m_cam->setNearClipDistance(3);

    Log(nope::log::Debug) << "Adding viewport '" << m_order << "' to window";
    m_viewport = m_win->addViewport(m_cam, m_order);
    m_viewport->setBackgroundColour(Ogre::ColourValue(0, 50, 0));
    m_cam->setAspectRatio(Ogre::Real(m_viewport->getActualWidth()) /
                          Ogre::Real(m_viewport->getActualHeight()));
    setActionMap();
    m_settings.loadFromFile(order);
  }

  LocalPlayer::LocalPlayer(LocalPlayer &&that)
      : m_data(that.m_data), m_cameraMode(std::move(that.m_cameraMode)),
        m_layers(std::move(that.m_layers)),
        m_currentLayers(std::move(that.m_currentLayers)), m_cam(that.m_cam),
        m_viewport(that.m_viewport), m_rounds(that.m_rounds),
        m_settings(that.m_settings), m_actions(that.m_actions),
        m_win(that.m_win), m_order(that.m_order)
  {
    that.m_cam = nullptr;
    that.m_viewport = nullptr;
    that.m_win = nullptr;
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
    std::cout << "left : " << left << ", top : " << top
              << ", width : " << width << ", height : " << height << std::endl;
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
	std::cout << "		Pressed for layer " << i << std::endl;
	if (m_currentLayers[i - 1]->keyPressed(ke))
	  {
	    return (true);
	  }
      }
    std::cout << std::endl;
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
    m_currentLayers.pop();
  }

  ACar &LocalPlayer::car()
  {
    return (m_data->car());
  }

  ACar const &LocalPlayer::car() const
  {
    return (m_data->car());
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
    std::cout << action << std::endl;
    return (m_actions[action]);
  }

  void LocalPlayer::speedUp()
  {
    m_data->car().move(-1);
  }

  void LocalPlayer::slowDown()
  {
    m_data->car().move(1);
  }

  void LocalPlayer::turnLeft()
  {
    m_data->car().turn(2);
  }

  void LocalPlayer::turnRight()
  {
    m_data->car().turn(-2);
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
    m_currentLayers.push(
        m_layers[static_cast<std::size_t>(GameLayer::Menu)].get());
  }

  void LocalPlayer::speedUpReleased()
  {
    m_data->car().move(0);
  }

  void LocalPlayer::slowDownReleased()
  {
    m_data->car().move(0);
  }

  void LocalPlayer::turnLeftReleased()
  {
    m_data->car().turn(0);
  }

  void LocalPlayer::turnRightReleased()
  {
    m_data->car().turn(0);
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
}
