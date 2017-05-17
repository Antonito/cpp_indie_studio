#ifndef CONTEXTGAME_HPP_
#define CONTEXTGAME_HPP_

#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>
#include "AContext.hpp"

// Forward declaration for faster compilation
namespace Ogre
{
  class RenderWindow;
}

namespace game
{
  class ContextGame final : public core::AContext,
                            public OIS::KeyListener,
                            public OIS::MouseListener
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

    virtual bool keyPressed(OIS::KeyEvent const &ke);
    virtual bool keyReleased(OIS::KeyEvent const &ke);

    virtual bool mouseMoved(OIS::MouseEvent const &me);
    virtual bool mousePressed(OIS::MouseEvent const &me,
                              OIS::MouseButtonID     id);
    virtual bool mouseReleased(OIS::MouseEvent const &me,
                               OIS::MouseButtonID     id);

  private:
    GameData                 m_game;
    std::vector<LocalPlayer> m_players;
  };
}

#endif // !CONTEXTGAME_HPP_
