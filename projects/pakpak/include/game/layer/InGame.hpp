#ifndef INGAME_HPP_
#define INGAME_HPP_

#include "ALayer.hpp"
#include "LocalPlayer.hpp"

namespace game
{
  class InGame final : public ALayer
  {
  public:
    InGame() = delete;
    InGame(GameData &data, LocalPlayer &layer, core::HUD *hud);
    InGame(InGame const &) = delete;
    InGame(InGame &&) = delete;
    virtual ~InGame();

    InGame &operator=(InGame const &) = delete;
    InGame &operator=(InGame &&) = delete;

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
    LocalPlayer &m_player;
  };
}

#endif // !INGAME_HPP_
