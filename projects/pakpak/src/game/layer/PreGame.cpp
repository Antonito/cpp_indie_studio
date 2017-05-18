#include "pakpak_stdafx.hpp"

namespace game
{
  PreGame::PreGame(GameData &data, ILayerStack &layer) : ALayer(data, layer)
  {
  }

  PreGame::~PreGame()
  {
  }

  void PreGame::enable()
  {
    m_layerStack.popLayer();
    m_layerStack.push(GameLayer::InGame);
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