#include "pakpak_stdafx.hpp"

namespace game
{
  PreGame::PreGame(GameData &data) : m_data(data)
  {
  }

  PreGame::~PreGame()
  {
  }

  void PreGame::enable()
  {
  }

  void PreGame::disable()
  {
  }

  void PreGame::update()
  {
  }

  void PreGame::display()
  {
  }

  bool PreGame::keyPressed(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool PreGame::keyReleased(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool PreGame::mouseMoved(OIS::MouseEvent const &)
  {
    return (false);
  }

  bool PreGame::mousePressed(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }

  bool PreGame::mouseReleased(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }
}