#include "pakpak_stdafx.hpp"

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
    switch (ke.key)
      {
      case OIS::KC_W:
	m_player.car().move(-1);
	break;
      case OIS::KC_S:
	m_player.car().move(1);
	break;
      case OIS::KC_A:
	m_player.car().turn(2);
	break;
      case OIS::KC_D:
	m_player.car().turn(-2);
	break;
      case OIS::KC_SPACE:
	m_player.car().move(0);
	break;
      default:
	return false;
      }
    return (true);
  }

  bool InGame::keyReleased(OIS::KeyEvent const &ke)
  {
    switch (ke.key)
      {
      case OIS::KC_W:
	m_player.car().move(0);
	break;
      case OIS::KC_S:
	m_player.car().move(0);
	break;
      case OIS::KC_A:
	m_player.car().turn(0);
	break;
      case OIS::KC_D:
	m_player.car().turn(0);
	break;
      default:
	return false;
      }
    return (true);
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
