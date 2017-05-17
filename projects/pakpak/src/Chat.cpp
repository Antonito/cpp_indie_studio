#include "pakpak_stdafx.hpp"

namespace game
{
  Chat::Chat(SpecData &data) : m_data(data)
  {
  }

  Chat::~Chat()
  {
  }

  void Chat::enable()
  {
  }

  void Chat::disable()
  {
  }

  void Chat::update()
  {
  }

  void Chat::display()
  {
  }

  bool Chat::keyPressed(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool Chat::keyReleased(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool Chat::mouseMoved(OIS::MouseEvent const &)
  {
    return (false);
  }

  bool Chat::mousePressed(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }

  bool Chat::mouseReleased(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }
}