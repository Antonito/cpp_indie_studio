#ifndef INGAME_HPP_
#define INGAME_HPP_

#include "ALayer.hpp"
#include "LocalPlayer.hpp"

namespace game
{
  enum SPEED_UNITS
  {
    U0,
    U1,
    U2,
    U3,
    U4,
    U5,
    U6,
    U7,
    U8,
    U9
  };

  enum POSITIONS
  {
    ST,
    ND,
    RD,
    TH
  };

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
    void setSpeed(std::uint32_t speed);
    void setPosition(std::uint32_t position);

  private:
    LocalPlayer &m_player;
    CEGUI::Window *m_speed[3];
    CEGUI::Window *m_positionSuffix;
    CEGUI::Window *m_positionPrefix;
  };
}

#endif // !INGAME_HPP_
