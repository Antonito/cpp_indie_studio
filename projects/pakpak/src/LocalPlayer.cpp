#include "pakpak_stdafx.hpp"

namespace game
{
  LocalPlayer::LocalPlayer(GameData &g, PlayerData &p)
      : m_data(p), m_cameraMode(CameraMode::Top), m_layers(), m_currentLayers()
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

    m_currentLayers.push(
        m_layers[static_cast<std::size_t>(GameLayer::Loading)].get());
  }

  bool LocalPlayer::keyPressed(OIS::KeyEvent const &ke)
  {
    for (std::int32_t i = m_currentLayers.size() - 1; i > 0; --i)
      {
	if (m_currentLayers[i]->keyPressed(ke))
	  {
	    return (true);
	  }
      }
    return (false);
  }

  bool LocalPlayer::keyReleased(OIS::KeyEvent const &ke)
  {
    for (std::int32_t i = m_currentLayers.size() - 1; i > 0; --i)
      {
	if (m_currentLayers[i]->keyReleased(ke))
	  {
	    return (true);
	  }
      }
    return (false);
  }

  bool LocalPlayer::mouseMoved(OIS::MouseEvent const &me)
  {
    for (std::int32_t i = m_currentLayers.size() - 1; i > 0; --i)
      {
	if (m_currentLayers[i]->mouseMoved(me))
	  {
	    return (true);
	  }
      }
    return (false);
  }

  bool LocalPlayer::mousePressed(OIS::MouseEvent const &me,
                                 OIS::MouseButtonID     id)
  {
    for (std::int32_t i = m_currentLayers.size() - 1; i > 0; --i)
      {
	if (m_currentLayers[i]->mousePressed(me, id))
	  {
	    return (true);
	  }
      }
    return (false);
  }

  bool LocalPlayer::mouseReleased(OIS::MouseEvent const &me,
                                  OIS::MouseButtonID     id)
  {
    for (std::int32_t i = m_currentLayers.size() - 1; i > 0; --i)
      {
	if (m_currentLayers[i]->mouseReleased(me, id))
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
}