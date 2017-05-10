#ifndef CONTEXTSPLASH_HPP_
#define CONTEXTSPLASH_HPP_

#include "IContext.hpp"

namespace core
{
  class ContextSplash final : public IContext
  {
  public:
    ContextSplash();
    ContextSplash(ContextSplash const &);
    ContextSplash(ContextSplash &&);
    virtual ~ContextSplash();

    ContextSplash &operator=(ContextSplash const &);
    ContextSplash &operator=(ContextSplash &&);

    virtual void update(std::vector<Event> &events);
    virtual void display(Renderer &renderer);

  private:
  };
}

#endif // !CONTEXTSPLASH_HPP_
