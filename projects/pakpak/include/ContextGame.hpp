#ifndef CONTEXTGAME_HPP_
#define CONTEXTGAME_HPP_

#include "AContext.hpp"

class Ogre::RenderWindow;

namespace game
{
  class ContextGame final : public core::AContext
  {
  public:
    ContextGame(Ogre::RenderWindow *win, core::InputListener *input);
    ContextGame(ContextGame const &);
    ContextGame(ContextGame &&);
    virtual ~ContextGame();

    ContextGame &operator=(ContextGame const &);
    ContextGame &operator=(ContextGame &&);

    virtual void enable();
    virtual void disable();

    virtual core::GameState update();
    virtual void            display();

  private:
  };
}

#endif // !CONTEXTGAME_HPP_