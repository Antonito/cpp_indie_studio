#include "pakpak_stdafx.hpp"

namespace game
{
  GameGUI::GameGUI(GameData &data, LocalPlayer &player, core::HUD *hud,
                   std::vector<std::unique_ptr<LocalPlayer>> &players)
      : ALayer(data, player, hud, players), m_player(player)
  {
    static_cast<void>(m_player); // TODO: rm
  }

  GameGUI::~GameGUI()
  {
  }

  void GameGUI::enable()
  {
  }

  void GameGUI::disable()
  {
    if (m_gui)
      m_gui->removeLayout("gui_ingame.layout");
  }

  void GameGUI::update()
  {
  }

  void GameGUI::display()
  {
  }

  bool GameGUI::keyPressed(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool GameGUI::keyReleased(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool GameGUI::mouseMoved(OIS::MouseEvent const &)
  {
    return (false);
  }

  bool GameGUI::mousePressed(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }

  bool GameGUI::mouseReleased(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }
}
