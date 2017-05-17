#ifndef LOCALPLAYER_HPP_
#define LOCALPLAYER_HPP_

#include <cstdint>
#include <array>
#include "GameData.hpp"
#include "PlayerData.hpp"
#include "CameraMode.hpp"
#include "GameLayer.hpp"
#include "FastStack.hpp"

namespace game
{
  class LocalPlayer
  {
  public:
    LocalPlayer() = delete;
    LocalPlayer(GameData &, PlayerData &);
    LocalPlayer(LocalPlayer const &) = delete;
    LocalPlayer(LocalPlayer &&) = delete;

    LocalPlayer &operator=(LocalPlayer const &) = delete;
    LocalPlayer &operator=(LocalPlayer &&) = delete;

  private:
    PlayerData &m_data;
    CameraMode  m_cameraMode;

    std::array<std::unique_ptr<ILayer>, GameLayer::NbLayer> m_layers;

    core::FastStack<ILayer *> m_currentLayers;
  };
}

#endif // !LOCALPLAYER_HPP_