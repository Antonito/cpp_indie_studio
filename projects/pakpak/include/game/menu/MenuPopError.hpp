//
// Created by duhieu_b on 18/06/17.
//

#ifndef CPP_INDIE_STUDIO_MENUPOPERROR_HPP
#define CPP_INDIE_STUDIO_MENUPOPERROR_HPP

#include "pakpak_stdafx.hpp"

namespace core
{
  class MenuPopError : public IMenuLayer
  {
  public:
    MenuPopError(menu::MenuManager &menuManager, GUI &gui,
                 SoundManager &sound);
    virtual ~MenuPopError()
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
    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

  private:
    MenuPopError(MenuPopError const &) = delete;
    MenuPopError(MenuPopError &&) = delete;
    MenuPopError &operator=(MenuPopError const &) = delete;
    void          initGUI();

    void soundClick();
    void soundPass();

    bool onOkClick(CEGUI::EventArgs const &);
    bool onOkArea(CEGUI::EventArgs const &);

    GUI &               m_gui;
    GameState           m_curState;
    menu::MenuManager & m_menuManager;
    core::SoundManager &m_sound;
  };
}

#endif // CPP_INDIE_STUDIO_MENUPOPERROR_HPP
