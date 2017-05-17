#ifndef CONTEXTGAME_HPP_
#define CONTEXTGAME_HPP_

#include "AContext.hpp"

// Forward declaration for faster compilation
namespace Ogre
{
  class RenderWindow;
}

namespace game
{
  class ContextGame final : public core::AContext
  {
  public:
    ContextGame(Ogre::RenderWindow *win, core::InputListener *input);
    ContextGame(ContextGame const &) = delete;
    ContextGame(ContextGame &&) = delete;
    virtual ~ContextGame();

    ContextGame &operator=(ContextGame const &) = delete;
    ContextGame &operator=(ContextGame &&) = delete;

    virtual void enable();
    virtual void disable();

    virtual core::GameState update();
    virtual void            display();

  private:
    GameData                 m_game;
    std::vector<LocalPlayer> m_players;
  };
}

#endif // !CONTEXTGAME_HPP_
