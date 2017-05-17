#ifndef ILAYERSTACK_HPP_
#define ILAYERSTACK_HPP_

#include "GameLayer.hpp"

namespace game
{
  class ILayerStack
  {
  public:
    virtual void push(GameLayer layer) = 0;
    virtual void popLayer() = 0;
  };
}

#endif // !ILAYERSTACK_HPP_