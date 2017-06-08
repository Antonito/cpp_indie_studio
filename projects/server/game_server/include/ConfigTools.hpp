#ifndef CONFIG_TOOLS_HPP_
#define CONFIG_TOOLS_HPP_

#include <string>
#include <map>
#include "Metadata.hpp"

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

// clang-format off
struct MapConfig
{
  //TODO check serialization std::map
  using map_t = std::map<std::string, std::string>;
  NOPE_SERIAL_MEMBER(
  std::string, name,
  std::string, directory,
  std::string, gameMode,
  int32_t,     nbLaps)
  map_t       md5;
};
// clang-format on

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif /* !CONFIG_TOOLS_HPP_ */
