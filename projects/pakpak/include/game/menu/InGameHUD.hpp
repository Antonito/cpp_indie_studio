//
// Created by brout_m on 12/06/17.
//

#ifndef CPP_INDIE_STUDIO_INGAMEHUD_HPP
#define CPP_INDIE_STUDIO_INGAMEHUD_HPP

#include "GUI.hpp"
#include "MenuManager.hpp"
#include "IMenuLayer.hpp"

namespace core
{
  class InGameHUD : public IMenuLayer
  {
  public:
    InGameHUD(menu::MenuManager &menuManager, GUI &gui);
    virtual ~InGameHUD()
    {
    }
    void      draw();
    void      entry();
    void      exit();
    void      destroy();
    GameState update() const;
    void      build();
    bool keyPressed(const OIS::KeyEvent &arg);
    bool mouseMoved(const OIS::MouseEvent &arg);
    bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    bool keyReleased(const OIS::KeyEvent &arg);

  private:
    InGameHUD(InGameHUD const &) = delete;
    InGameHUD(InGameHUD &&) = delete;
    InGameHUD &        operator=(InGameHUD const &) = delete;
    InGameHUD &        operator=(InGameHUD &&) = delete;
    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

    GUI &              m_gui;
    GameState          m_curState;
    menu::MenuManager &m_menuManager;
  };
}

#endif // CPP_INDIE_STUDIO_INGAMEHUD_HPP
