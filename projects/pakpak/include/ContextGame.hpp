#ifndef CONTEXTGAME_HPP_
#define CONTEXTGAME_HPP_

#include "IContext.hpp"

namespace core
{
  class ContextGame final : public IContext
  {
  public:
    ContextGame();
    ContextGame(ContextGame const &);
    ContextGame(ContextGame &&);
    virtual ~ContextGame();

    ContextGame &operator=(ContextGame const &);
    ContextGame &operator=(ContextGame &&);

    virtual void update(std::vector<Event> &events);
    virtual void display(Renderer &renderer);

  private:
  };
}

#endif // !CONTEXTGAME_HPP_
