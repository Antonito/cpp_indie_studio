#include "pakpak_stdafx.hpp"

namespace game
{
  Loading::Loading(GameData &data, ILayerStack &layer) : ALayer(data, layer)
  {
  }

  Loading::~Loading()
  {
  }

  void Loading::enable()
  {
  }

  void Loading::disable()
  {
  }

  void Loading::update()
  {
  }

  void Loading::display()
  {
  }

  bool Loading::keyPressed(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool Loading::keyReleased(OIS::KeyEvent const &)
  {
    return (false);
  }

  bool Loading::mouseMoved(OIS::MouseEvent const &)
  {
    return (false);
  }

  bool Loading::mousePressed(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }

  bool Loading::mouseReleased(OIS::MouseEvent const &, OIS::MouseButtonID)
  {
    return (false);
  }
}