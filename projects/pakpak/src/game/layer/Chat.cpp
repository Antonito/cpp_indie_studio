#include "pakpak_stdafx.hpp"

namespace game
{
  Chat::Chat(GameData &data, ILayerStack &layer, core::HUD *hud,
             std::vector<std::unique_ptr<LocalPlayer>> &players)
      : ALayer(data, layer, hud, players)
  {
  }

  Chat::~Chat()
  {
  }

  void Chat::enable()
  {
  }

  void Chat::disable()
  {
  }

  void Chat::update()
  {
  }

  void Chat::display()
  {
  }

  bool Chat::keyPressed(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool Chat::keyReleased(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool Chat::mouseMoved(OIS::MouseEvent const &)
  {
    return (false);
  }

  bool Chat::mousePressed(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }

  bool Chat::mouseReleased(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }
}
