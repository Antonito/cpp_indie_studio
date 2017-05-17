#ifndef LOCALPLAYER_HPP_
#define LOCALPLAYER_HPP_

#include <cstdint>

namespace game
{
  class PlayerData;
  enum class CameraMode : std::int8_t;

  class LocalPlayer
  {
  public:
    LocalPlayer() = delete;
    LocalPlayer(PlayerData &);
    LocalPlayer(LocalPlayer const &) = delete;
    LocalPlayer(LocalPlayer &&) = delete;

    LocalPlayer &operator=(LocalPlayer const &) = delete;
    LocalPlayer &operator=(LocalPlayer &&) = delete;

  private:
    PlayerData &m_data;
    CameraMode  m_cameraMode;
  };
}

#endif // !LOCALPLAYER_HPP_