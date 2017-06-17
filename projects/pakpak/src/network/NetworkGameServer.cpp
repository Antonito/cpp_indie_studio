#include "pakpak_stdafx.hpp"

namespace core
{
  GameServer::GameServer(std::string const &_addr, std::uint16_t const _port,
                         std::uint16_t const _clients,
                         std::uint16_t const _maxClients)
      : address(_addr), port(_port), clients(_clients), maxClients(_maxClients)
  {
  }
}
