#ifndef ILAYERSTACK_HPP_
#define ILAYERSTACK_HPP_

#include <GameState.hpp>
#include "GameLayer.hpp"

// Disable clang warning for vtable
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

namespace game
{
  class ILayerStack
  {
  public:
    virtual ~ILayerStack()
    {
    }

    virtual void push(GameLayer layer) = 0;

    virtual void popLayer() = 0;
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !ILAYERSTACK_HPP_
