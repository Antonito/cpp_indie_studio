#include "pakpak_stdafx.hpp"

namespace game
{
  LocalPlayer::LocalPlayer(Ogre::RenderWindow *win, GameData &g, PlayerData *p,
                           int order)
      : m_data(p), m_cameraMode(CameraMode::Top), m_layers(),
        m_currentLayers(), m_cam(nullptr), m_viewport(nullptr)
  {
    if (p == nullptr)
      {
	std::cout << " DAAAAAAAAAFUUUUUUUUUUUQQQQQQQQQ" << std::endl;
      }
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

    m_viewport = win->addViewport(m_cam, order);
    m_viewport->setBackgroundColour(Ogre::ColourValue(0, 50, 0));
    m_cam->setAspectRatio(Ogre::Real(m_viewport->getActualWidth()) /
                          Ogre::Real(m_viewport->getActualHeight()));
  }

  LocalPlayer::LocalPlayer(LocalPlayer &&that)
      : m_data(that.m_data), m_cameraMode(std::move(that.m_cameraMode)),
        m_layers(std::move(that.m_layers)),
        m_currentLayers(std::move(that.m_currentLayers)), m_cam(that.m_cam),
        m_viewport(that.m_viewport)
  {
    that.m_cam = nullptr;
    that.m_viewport = nullptr;
  }

  LocalPlayer::~LocalPlayer()
  {
  }

  void LocalPlayer::setViewPort(Ogre::Real left, Ogre::Real top,
                                Ogre::Real width, Ogre::Real height)
  {
    std::cout << "left : " << left << ", top : " << top
              << ", width : " << width << ", height : " << height << std::endl;
    m_viewport->setDimensions(left, top, width, height);
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
    std::cout << this << std::endl;
    std::cout << m_data << std::endl;
    return (m_data->car());
  }

  ACar const &LocalPlayer::car() const
  {
    return (m_data->car());
  }
}
