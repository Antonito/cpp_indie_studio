#include "pakpak_stdafx.hpp"

namespace game
{
  PostGame::PostGame(GameData &data, ILayerStack &layer, core::HUD *hud)
      : ALayer(data, layer, hud)
  {
  }

  PostGame::~PostGame()
  {
  }

  void PostGame::enable()
  {
  }

  void PostGame::disable()
  {
  }

  void PostGame::update()
  {
  }

  void PostGame::display()
  {
  }

  bool PostGame::keyPressed(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool PostGame::keyReleased(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool PostGame::mouseMoved(OIS::MouseEvent const &)
  {
    return (false);
  }

  bool PostGame::mousePressed(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }

  bool PostGame::mouseReleased(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }
}
