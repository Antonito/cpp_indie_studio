#ifndef ILAYERSTACK_HPP_
#define ILAYERSTACK_HPP_

#include <GameState.hpp>
#include "GameLayer.hpp"

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

#endif // !ILAYERSTACK_HPP_
