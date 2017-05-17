#ifndef CAMERAMODE_HPP_
#define CAMERAMODE_HPP_

#include <cstdint>

namespace game
{
  enum class CameraMode : std::int8_t
  {
    FirstPerson,
    ThirdPerson,
    Top,
    CarFront,
    CarSideLeft,
    CarSideRight,
  };
}

#endif // !CAMERAMODE_HPP_