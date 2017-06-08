#ifndef CONFIG_TOOLS_HPP_
#define CONFIG_TOOLS_HPP_

#include <string>
#include "Metadata.hpp"

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

// clang-format off
struct MapConfig
{
  NOPE_SERIAL_MEMBER(
  std::string, name,
  std::string, directory,
  std::string, gameMode,
  int32_t,     nbLaps
  )
};
// clang-format on

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif /* !CONFIG_TOOLS_HPP_ */
