#include "pakpak_stdafx.hpp"

namespace game
{
  ALayer::ALayer(GameData &gameData, ILayerStack &layerStack)
      : m_gameData(gameData), m_layerStack(layerStack)
  {
  }

  ALayer::~ALayer()
  {
  }
}
