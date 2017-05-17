#ifndef ILAYER_HPP_
#define ILAYER_HPP_

#include "IEventHandler.hpp"

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

#endif // !ILAYER_HPP_
