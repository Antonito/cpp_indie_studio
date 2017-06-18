#ifndef NETWORK_GAME_HPP_
#define NETWORK_GAME_HPP_

namespace core
{
  class NetworkGame
  {
  public:
    NetworkGame();
    ~NetworkGame();

    NetworkGame(NetworkGame const &) = delete;
    NetworkGame &operator=(NetworkGame const &) = delete;

    void init();
    void run();

  private:
  };
}

#endif // !NETWORK_GAME_HPP_
