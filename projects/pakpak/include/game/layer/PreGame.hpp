#ifndef PREGAME_HPP_
#define PREGAME_HPP_

#include "ALayer.hpp"

namespace game
{
  class PreGame final : public ALayer
  {
  public:
    PreGame() = delete;
    PreGame(GameData &data, ILayerStack &layer, core::HUD *hud);
    PreGame(PreGame const &) = delete;
    PreGame(PreGame &&) = delete;
    virtual ~PreGame();

    PreGame &operator=(PreGame const &) = delete;
    PreGame &operator=(PreGame &&) = delete;

    virtual void enable();
    virtual void disable();

    virtual void update();
    virtual void display();

    virtual bool keyPressed(OIS::KeyEvent const &ke);
    virtual bool keyReleased(OIS::KeyEvent const &ke);

    virtual bool mouseMoved(OIS::MouseEvent const &me);
    virtual bool mousePressed(OIS::MouseEvent const &me,
                              OIS::MouseButtonID     id);
    virtual bool mouseReleased(OIS::MouseEvent const &me,
                               OIS::MouseButtonID     id);

  private:
  };
}

#endif // !PREGAME_HPP_
