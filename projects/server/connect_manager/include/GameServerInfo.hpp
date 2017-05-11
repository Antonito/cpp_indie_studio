#ifndef GAME_SERVER_INFO_HPP_
#define GAME_SERVER_INFO_HPP_

#include <cstdint>
#include "GenNetwork.hpp"

struct GameServerInfo
{
  GameServerInfo(std::array<char, INET6_ADDRSTRLEN> _addr,
                 std::uint16_t const _port,
                 std::uint16_t const _currentClients,
                 std::uint16_t const _maxClients)
      : addr(_addr), port(_port), currentClients(_currentClients),
        maxClients(_maxClients)
  {
  }

  std::array<char, INET6_ADDRSTRLEN> addr;
  std::uint16_t port;
  std::uint16_t currentClients;
  std::uint16_t maxClients;
};

#endif // !GAME_SERVER_INFO_HPP_
