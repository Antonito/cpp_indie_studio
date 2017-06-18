//
// Created by brout_m on 15/06/17.
//

#ifndef CPP_INDIE_STUDIO_PAUSER_HPP
#define CPP_INDIE_STUDIO_PAUSER_HPP

namespace game
{
  class Pauser
  {
  public:
    Pauser();
    ~Pauser();
    Pauser &operator=(Pauser const &) = delete;
    Pauser &operator=(Pauser &&) = delete;
    Pauser(Pauser const &) = delete;
    Pauser(Pauser &&) = delete;
    static void pause();
    static void unpause();
    static bool isPaused();

  private:
    static bool m_pause;
  };
}

#endif // CPP_INDIE_STUDIO_PAUSER_HPP
