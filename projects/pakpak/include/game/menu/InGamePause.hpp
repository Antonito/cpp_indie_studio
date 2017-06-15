//
// Created by brout_m on 12/06/17.
//

#ifndef CPP_INDIE_STUDIO_INGAMEPAUSE_HPP
#define CPP_INDIE_STUDIO_INGAMEPAUSE_HPP

#include "GUI.hpp"
#include "MenuManager.hpp"
#include "IMenuLayer.hpp"

namespace core
{
  class InGamePause : public IMenuLayer
  {
  public:
    InGamePause(menu::MenuManager &menuManager, GUI &gui);
    virtual ~InGamePause(){};
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
    InGamePause(InGamePause const &) = delete;
    InGamePause(InGamePause &&) = delete;
    InGamePause &      operator=(InGamePause const &) = delete;
    InGamePause &      operator=(InGamePause &&) = delete;
    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

    GUI &              m_gui;
    GameState          m_curState;
    menu::MenuManager &m_menuManager;

    bool onBackClick(CEGUI::EventArgs const &);
  };
}

#endif // CPP_INDIE_STUDIO_INGAMEPAUSE_HPP
