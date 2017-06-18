#ifndef NETWORK_GAME_HPP_
#define NETWORK_GAME_HPP_

#include <cstdint>
#include <memory>
#include <string>
#include "UDPSocket.hpp"

namespace core
{
  class NetworkGame
  {
  public:
    NetworkGame();
    ~NetworkGame();

    NetworkGame(NetworkGame const &) = delete;
    NetworkGame &operator=(NetworkGame const &) = delete;

    void init(std::uint16_t const port, std::string const &addr);
    void run();

  private:
    std::shared_ptr<network::UDPSocket> m_sock;
  };
}

#endif // !NETWORK_GAME_HPP_
