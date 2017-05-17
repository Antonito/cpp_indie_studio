#include "pakpak_stdafx.hpp"

namespace game
{
  LocalPlayer::LocalPlayer(PlayerData &p)
      : m_data(p), m_cameraMode(CameraMode::Top)
  {
  }
}