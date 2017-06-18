#include "pakpak_stdafx.hpp"

namespace game
{
  Score::Score(GameData &data, ILayerStack &layer, core::HUD *hud,
               std::vector<std::unique_ptr<LocalPlayer>> &players)
      : ALayer(data, layer, hud, players)
  {
  }

  Score::~Score()
  {
  }

  void Score::enable()
  {
  }

  void Score::disable()
  {
  }

  void Score::update()
  {
  }

  void Score::display()
  {
  }

  bool Score::keyPressed(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool Score::keyReleased(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool Score::mouseMoved(OIS::MouseEvent const &)
  {
    return (false);
  }

  bool Score::mousePressed(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }

  bool Score::mouseReleased(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }
}
