#ifndef NETWORK_GAME_HPP_
#define NETWORK_GAME_HPP_

#include <cstdint>

namespace core
{
  class NetworkGame
  {
  public:
    NetworkGame();
    ~NetworkGame();

    NetworkGame(NetworkGame const &) = delete;
    NetworkGame &operator=(NetworkGame const &) = delete;

    void init(std::uint16_t const port);
    void run();

  private:
  };
}

#endif // !NETWORK_GAME_HPP_
