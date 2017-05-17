#include "pakpak_stdafx.hpp"

namespace game
{
  Menu::Menu(GameData &data) : m_data(data)
  {
  }

  Menu::~Menu()
  {
  }

  void Menu::enable()
  {
  }

  void Menu::disable()
  {
  }

  void Menu::update()
  {
  }

  void Menu::display()
  {
  }

  bool Menu::keyPressed(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool Menu::keyReleased(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool Menu::mouseMoved(OIS::MouseEvent const &)
  {
    return (false);
  }

  bool Menu::mousePressed(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }

  bool Menu::mouseReleased(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }
}