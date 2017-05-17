#include "pakpak_stdafx.hpp"

namespace game
{
  LocalPlayer::LocalPlayer(GameData &g, PlayerData &p)
      : m_data(p), m_cameraMode(CameraMode::Top), m_layers(), m_currentLayers()
  {
    m_layers[GameLayer::Loading] = std::make_unique<Loading>(g);
    m_layers[GameLayer::PreGame] = std::make_unique<PreGame>(g);
    m_layers[GameLayer::InGame] = std::make_unique<InGame>(g, *this);
    m_layers[GameLayer::GameGUI] = std::make_unique<GameGUI>(g, *this);
    m_layers[GameLayer::Spectator] = std::make_unique<Spectator>(g);
    m_layers[GameLayer::SpecGUI] = std::make_unique<SpecGUI>(g);
    m_layers[GameLayer::PostGame] = std::make_unique<PostGame>(g);
    m_layers[GameLayer::Score] = std::make_unique<Score>(g);
    m_layers[GameLayer::Chat] = std::make_unique<Chat>(g);
    m_layers[GameLayer::Menu] = std::make_unique<Menu>(g);
  }
}