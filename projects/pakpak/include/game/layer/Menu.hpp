#ifndef MENU_HPP_
#define MENU_HPP_

#include <CEGUI/InputEvent.h>
#include "LocalPlayer.hpp"
#include "HUD.hpp"
#include "ALayer.hpp"

namespace game
{
  class Menu final : public ALayer
  {
  public:
    enum BUTTONS
    {
      PAUSE_SETTINGS,
      PAUSE_RESUME,
      PAUSE_QUIT
    };

    Menu() = delete;
    Menu(GameData &data, ILayerStack &layer, core::HUD *hud,
         std::vector<std::unique_ptr<LocalPlayer>> &players);
    Menu(Menu const &) = delete;
    Menu(Menu &&) = delete;
    virtual ~Menu();

    Menu &operator=(Menu const &) = delete;
    Menu &operator=(Menu &&) = delete;

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
    bool               onResumeClick(CEGUI::EventArgs const &);
    bool               onQuitClick(CEGUI::EventArgs const &);
    CEGUI::MouseButton convertButton(OIS::MouseButtonID);
  };
}

#endif // !MENU_HPP_
