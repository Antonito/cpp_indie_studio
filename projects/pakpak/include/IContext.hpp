#ifndef ICONTEXT_HPP_
#define ICONTEXT_HPP_

#include <vector>

namespace core
{
  class IContext
  {
  public:
    virtual ~IContext()
    {
    }

    virtual void update(std::vector<Event> &events) = 0;
    virtual void display(Renderer &renderer) = 0;
  };
}

#endif // !ICONTEXT_HPP_
