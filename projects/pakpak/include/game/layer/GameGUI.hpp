#ifndef GAMEGUI_HPP_
#define GAMEGUI_HPP_

#include "ALayer.hpp"
#include "LocalPlayer.hpp"

namespace game
{
  class GameGUI final : public ALayer
  {
  public:
    GameGUI() = delete;
    GameGUI(GameData &data, LocalPlayer &layer, core::HUD *hud);
    GameGUI(GameGUI const &) = delete;
    GameGUI(GameGUI &&) = delete;
    virtual ~GameGUI();

    GameGUI &operator=(GameGUI const &) = delete;
    GameGUI &operator=(GameGUI &&) = delete;

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

#endif // !GAMEGUI_HPP_
