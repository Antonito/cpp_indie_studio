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

  bool InGame::keyPressed(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool InGame::keyReleased(OIS::KeyEvent const &)
  {
    return (false);
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