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

    //     switch (ke.key)
    //       {
    //       case OIS::KC_UP:
    // 	m_player.car().move(-1);
    // 	break;
    //       case OIS::KC_S:
    // 	m_player.car().move(1);
    // 	break;
    //       case OIS::KC_A:
    // 	m_player.car().turn(2);
    // 	break;
    //       case OIS::KC_D:
    // 	m_player.car().turn(-2);
    // 	break;
    //       default:
    // 	return false;
    //       }
    //     return (true);
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
    //     switch (ke.key)
    //       {
    //       case OIS::KC_UP:
    // 	m_player.car().move(0);
    // 	break;
    //       case OIS::KC_S:
    // 	m_player.car().move(0);
    // 	break;
    //       case OIS::KC_A:
    // 	m_player.car().turn(0);
    // 	break;
    //       case OIS::KC_D:
    // 	m_player.car().turn(0);
    // 	break;
    //       default:
    // 	return false;
    //       }
    //     return (true);
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
