#include "pakpak_stdafx.hpp"

namespace game
{
  ALayer::ALayer(GameData &gameData, ILayerStack &layerStack, core::HUD *hud,
                 std::vector<std::unique_ptr<LocalPlayer>> &players)
      : m_gameData(gameData), m_layerStack(layerStack), m_gui(hud),
        m_players(players)
  {
  }

  ALayer::~ALayer()
  {
  }
}
