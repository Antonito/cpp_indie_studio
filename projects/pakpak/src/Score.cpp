#include "pakpak_stdafx.hpp"

namespace game
{
  Score::Score(SpecData &data) : m_data(data)
  {
  }

  Score::~Score()
  {
  }

  void Score::enable()
  {
  }

  void Score::disable()
  {
  }

  void Score::update()
  {
  }

  void Score::display()
  {
  }

  bool Score::keyPressed(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool Score::keyReleased(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool Score::mouseMoved(OIS::MouseEvent const &)
  {
    return (false);
  }

  bool Score::mousePressed(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }

  bool Score::mouseReleased(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }
}