#include "pakpak_stdafx.hpp"

namespace game
{
  InGame::InGame(GameData &data, LocalPlayer &player, core::HUD *hud)
      : ALayer(data, player, hud), m_player(player)
  {
  }

  InGame::~InGame()
  {
  }

  void InGame::enable()
  {
    nope::log::Log(Debug) << "Enabling InGame";
    if (m_gui)
      m_gui->loadLayout("gui_ingame.layout");
  }

  void InGame::disable()
  {
  }

  void InGame::update()
  {
  }

  void InGame::display()
  {
  }

  bool InGame::keyPressed(OIS::KeyEvent const &ke)
  {
    std::string action = m_player.settings().actionForKey(
        static_cast<std::size_t>(m_player.order()), ke.key);

    if (action == "NO_ACTION")
      {
	return false;
      }
    nope::log::Log(Info) << "DOING ACTION";
    void (LocalPlayer::*ptr)() = m_player.actions(action).first;
    (m_player.*ptr)();
    return true;
  }

  bool InGame::keyReleased(OIS::KeyEvent const &ke)
  {
    std::string action = m_player.settings().actionForKey(
        static_cast<std::size_t>(m_player.order()), ke.key);
    if (action == "NO_ACTION")
      {
	return false;
      }
    nope::log::Log(Info) << "DOING ACTION";
    void (LocalPlayer::*ptr)() = m_player.actions(action).second;
    (m_player.*ptr)();
    return true;
  }

  bool InGame::mouseMoved(OIS::MouseEvent const &)
  {

    return (false);
  }

  bool InGame::mousePressed(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }

  bool InGame::mouseReleased(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }
}
