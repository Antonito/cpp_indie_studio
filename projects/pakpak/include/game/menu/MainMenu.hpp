//
// Created by duhieu_b on 23/05/17.
//

#ifndef CPP_INDIE_STUDIO_MAINMENU_HPP_
#define CPP_INDIE_STUDIO_MAINMENU_HPP_

#include "IMenuLayer.hpp"
#include "GUI.hpp"
#include "MenuManager.hpp"

namespace core
{
  class MainMenu : public IMenuLayer
  {
  public:
    MainMenu(menu::MenuManager &menuManager, GUI &gui);
    virtual ~MainMenu()
    {
    }
    void entry();
    void destroy();
    void draw();
    void exit();
    void build();
    bool keyPressed(const OIS::KeyEvent &arg);
    bool mouseMoved(const OIS::MouseEvent &arg);
    bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    bool keyReleased(const OIS::KeyEvent &arg);
    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);
    GameState update() const;

  private:
    MainMenu(MainMenu const &) = delete;
    MainMenu(MainMenu &&) = delete;
    MainMenu &operator=(MainMenu const &) = delete;
    void      initGUI();
    bool      onExitClick(CEGUI::EventArgs const &);
    bool      onSoloClick(CEGUI::EventArgs const &);
    bool      onMultiClick(CEGUI::EventArgs const &);
    bool      onOptionClick(CEGUI::EventArgs const &);
    bool      onScoreClick(CEGUI::EventArgs const &);

    GUI &              m_gui;
    GameState          m_curState;
    menu::MenuManager &m_menuManager;
  };
}

#endif // CPP_INDIE_STUDIO_MAINMENU_HPP_
