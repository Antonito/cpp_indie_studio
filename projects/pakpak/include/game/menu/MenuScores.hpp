//
// Created by brout_m on 12/06/17.
//

#ifndef CPP_INDIE_STUDIO_SCORES_HPP
#define CPP_INDIE_STUDIO_SCORES_HPP

#include "GUI.hpp"
#include "MenuManager.hpp"
#include "IMenuLayer.hpp"

namespace core
{
  class MenuScores : public IMenuLayer
  {
  public:
    MenuScores(menu::MenuManager &menuManager, GUI &gui,
               SettingsPlayer &settings, SoundManager &sound);
    virtual ~MenuScores(){};
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
    MenuScores(MenuScores const &) = delete;
    MenuScores(MenuScores &&) = delete;
    MenuScores &       operator=(MenuScores const &) = delete;
    MenuScores &       operator=(MenuScores &&) = delete;
    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

    GUI &              m_gui;
    GameState          m_curState;
    menu::MenuManager &m_menuManager;
    SettingsPlayer &   m_settings;
    SoundManager &     m_sound;

    bool onBackClick(CEGUI::EventArgs const &);
    bool onBackArea(CEGUI::EventArgs const &);

    void soundPass();
    void soundClick();
  };
}

#endif // CPP_INDIE_STUDIO_SCORES_HPP
