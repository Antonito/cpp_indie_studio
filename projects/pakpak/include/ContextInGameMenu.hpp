#ifndef CONTEXTINGAMEMENU_HPP_
#define CONTEXTINGAMEMENU_HPP_

#include "IContext.hpp"

namespace core
{
  class ContextInGameMenu final : public IContext
  {
  public:
    ContextInGameMenu();
    ContextInGameMenu(ContextInGameMenu const &);
    ContextInGameMenu(ContextInGameMenu &&);
    virtual ~ContextInGameMenu();

    ContextInGameMenu &operator=(ContextInGameMenu const &);
    ContextInGameMenu &operator=(ContextInGameMenu &&);

    virtual void update(std::vector<Event> &events);
    virtual void display(Renderer &renderer);

  private:
  };
}

#endif // !CONTEXTINGAMEMENU_HPP_
