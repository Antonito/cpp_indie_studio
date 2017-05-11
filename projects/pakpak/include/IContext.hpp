#ifndef ICONTEXT_HPP_
#define ICONTEXT_HPP_

#include <vector>
#include <cstdint>

namespace core
{
  enum class GameState : std::int8_t;

  class IContext
  {
  public:
    virtual ~IContext()
    {
    }

    virtual void enable() = 0;
    virtual void disable() = 0;

    virtual GameState update() = 0;
    virtual void      display() = 0;
  };
}

#endif // !ICONTEXT_HPP_
