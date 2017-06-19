#include "pakpak_stdafx.hpp"

namespace game
{
  SpecGUI::SpecGUI(GameData &data, ILayerStack &layer, core::HUD *hud)
      : ALayer(data, layer, hud)
  {
  }

  SpecGUI::~SpecGUI()
  {
  }

  void SpecGUI::enable()
  {
  }

  void SpecGUI::disable()
  {
  }

  void SpecGUI::update()
  {
  }

  void SpecGUI::display()
  {
  }

  bool SpecGUI::keyPressed(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool SpecGUI::keyReleased(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool SpecGUI::mouseMoved(OIS::MouseEvent const &)
  {
    return (false);
  }

  bool SpecGUI::mousePressed(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }

  bool SpecGUI::mouseReleased(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }
}
