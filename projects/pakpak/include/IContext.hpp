#ifndef ICONTEXT_HPP_
#define ICONTEXT_HPP_

#include <vector>
#include <cstdint>

// Disable clang warning for vtable
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

namespace core
{
  // Forward declaration for faster compilation
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

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !ICONTEXT_HPP_
