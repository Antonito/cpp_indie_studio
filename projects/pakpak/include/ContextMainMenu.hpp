#ifndef CONTEXTMAINMENU_HPP_
#define CONTEXTMAINMENU_HPP_

#include "IContext.hpp"

namespace core
{
  class ContextMainMenu final : public IContext
  {
  public:
    ContextMainMenu();
    ContextMainMenu(ContextMainMenu const &);
    ContextMainMenu(ContextMainMenu &&);
    virtual ~ContextMainMenu();

    ContextMainMenu &operator=(ContextMainMenu const &);
    ContextMainMenu &operator=(ContextMainMenu &&);

    virtual void update(std::vector<Event> &events);
    virtual void display(Renderer &renderer);

  private:
  };
}

#endif // !CONTEXTMAINMENU_HPP_
