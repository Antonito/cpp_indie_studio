#include "pakpak_stdafx.hpp"
#include <functional>

namespace game
{
  InGame::InGame(GameData &data, LocalPlayer &player)
      : ALayer(data, player), m_player(player)
  {
  }

  InGame::~InGame()
  {
  }

  void InGame::enable()
  {
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
    std::string action =
        m_player.settings().actionForKey(m_player.order(), ke.key);

    if (action == "NO_ACTION")
      {
	return false;
      }
    std::cout << "DOING ACTION" << std::endl;
    void (LocalPlayer::*ptr)() = m_player.actions(action).first;
    (m_player.*ptr)();
    return true;
  }

  bool InGame::keyReleased(OIS::KeyEvent const &ke)
  {

    std::string action =
        m_player.settings().actionForKey(m_player.order(), ke.key);

    if (action == "NO_ACTION")
      {
	return false;
      }
    std::cout << "DOING ACTION" << std::endl;
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
