#include "pakpak_stdafx.hpp"

namespace core
{
  GameServer::GameServer(std::string const &_addr, std::uint16_t const _port,
                         std::uint16_t const _clients,
                         std::uint16_t const _maxClients)
      : address(_addr), port(_port), clients(_clients), maxClients(_maxClients)
  {
  }

  GameServer &GameServer::operator=(GameServer const &that)
  {
    if (this != &that)
      {
	address = that.address;
	port = that.port;
	clients = that.clients;
	maxClients = that.maxClients;
      }
    return *this;
  }

  GameServer::GameServer() : address(""), port(0), clients(0), maxClients(0)
  {
  }
}
