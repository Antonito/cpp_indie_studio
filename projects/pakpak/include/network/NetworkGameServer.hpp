#ifndef NETWORK_GAME_SERVER_HPP_
#define NETWORK_GAME_SERVER_HPP_

#include <string>
#include <cstdint>

namespace core
{
  struct GameServer
  {
    GameServer(std::string const &_addr, std::uint16_t const _port,
               std::uint16_t const _clients, std::uint16_t const _maxClients);

    std::string   address;
    std::uint16_t port;
    std::uint16_t clients;
    std::uint16_t maxClients;
  };
}

#endif // !NETWORK_GAME_SERVER_HPP_
