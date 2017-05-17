#include "pakpak_stdafx.hpp"

namespace game
{
  GameGUI::GameGUI(GameData &data) : m_data(data)
  {
  }

  GameGUI::~GameGUI()
  {
  }

  void GameGUI::enable()
  {
  }

  void GameGUI::disable()
  {
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