#ifndef ISUBCONTEXT_HPP_
#define ISUBCONTEXT_HPP_

#include <vector>
#include <cstdint>

namespace core
{
  // Forward declaration for faster compilation
  enum class GameState : std::int8_t;

  class ISubContext
  {
  public:
    virtual ~ISubContext()
    {
    }

    virtual void enable() = 0;
    virtual void disable() = 0;

    virtual InGameState update() = 0;
    virtual void        display() = 0;
  };
}

#endif // !ISUBCONTEXT_HPP_
