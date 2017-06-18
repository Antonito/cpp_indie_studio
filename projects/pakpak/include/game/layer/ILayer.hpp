#ifndef ILAYER_HPP_
#define ILAYER_HPP_

#include "IEventHandler.hpp"

// Disable clang warning for vtable
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

namespace game
{
  class ILayer : public IEventHandler
  {
  public:
    virtual ~ILayer()
    {
    }

    virtual void enable() = 0;
    virtual void disable() = 0;

    virtual void update() = 0;
    virtual void display() = 0;
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !ILAYER_HPP_
