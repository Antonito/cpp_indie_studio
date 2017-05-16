#ifndef SUBCONTEXTMENU_HPP_
#define SUBCONTEXTMENU_HPP_

#include "ASubContext.hpp"

namespace game
{
  class SubContextMenu final : public core::ASubContext
  {
  public:
    SubContextMenu(core::AContext *parentContext);
    SubContextMenu(SubContextMenu const &) = delete;
    SubContextMenu(SubContextMenu &&) = delete;
    virtual ~SubContextMenu();

    SubContextMenu &operator=(SubContextMenu const &) = delete;
    SubContextMenu &operator=(SubContextMenu &&) = delete;

    virtual void enable();
    virtual void disable();

    virtual core::InGameState update();
    virtual void              display();

  private:
  };
}

#endif // !SUBCONTEXTMENU_HPP_
