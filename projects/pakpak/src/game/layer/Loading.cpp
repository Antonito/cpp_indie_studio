#include "pakpak_stdafx.hpp"

namespace game
{
  Loading::Loading(GameData &data, ILayerStack &layer, core::HUD *hud)
      : ALayer(data, layer, hud), m_start()
  {
  }

  Loading::~Loading()
  {
  }

  void Loading::enable()
  {
    m_start = clock_t::now();
  }

  void Loading::disable()
  {
  }

  void Loading::update()
  {
    using milliseconds = std::chrono::milliseconds;

    std::int64_t ms =
        std::chrono::duration_cast<milliseconds>(clock_t::now() - m_start)
            .count();

    if (ms > 1000)
      {
	m_layerStack.popLayer();
	m_layerStack.push(GameLayer::PreGame);
      }
  }

  void Loading::display()
  {
  }

  bool Loading::keyPressed(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool Loading::keyReleased(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool Loading::mouseMoved(OIS::MouseEvent const &)
  {
    return (false);
  }

  bool Loading::mousePressed(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }

  bool Loading::mouseReleased(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }
}
