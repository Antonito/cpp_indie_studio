#include "pakpak_stdafx.hpp"

namespace game
{
  Spectator::Spectator(GameData &data) : m_data(data)
  {
  }

  Spectator::~Spectator()
  {
  }

  void Spectator::enable()
  {
  }

  void Spectator::disable()
  {
  }

  void Spectator::update()
  {
  }

  void Spectator::display()
  {
  }

  bool Spectator::keyPressed(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool Spectator::keyReleased(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool Spectator::mouseMoved(OIS::MouseEvent const &)
  {
    return (false);
  }

  bool Spectator::mousePressed(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }

  bool Spectator::mouseReleased(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }
}