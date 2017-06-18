#include "pakpak_stdafx.hpp"

namespace game
{
  ALayer::ALayer(GameData &gameData, ILayerStack &layerStack, core::HUD *hud)
      : m_gameData(gameData), m_layerStack(layerStack), m_gui(hud)
  {
  }

  ALayer::~ALayer()
  {
  }
}
