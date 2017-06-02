//
// Created by duhieu_b on 23/05/17.
//

#ifndef CPP_INDIE_STUDIO_MAINMENU_HPP_
#define CPP_INDIE_STUDIO_MAINMENU_HPP_

#include "IMenuLayer.hpp"
#include "GUI.hpp"

namespace core
{
  class MainMenu : public IMenuLayer
  {
  public:
    MainMenu();
    virtual ~MainMenu()
    {
    }
    void draw();
    void entry();
    void exit();
    void destroy();

    bool keyPressed(const OIS::KeyEvent &arg);
    bool mouseMoved(const OIS::MouseEvent &arg);
    bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    bool keyReleased(const OIS::KeyEvent &arg);
    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);
    GameState update() const;
    void      build();

  private:
    MainMenu(MainMenu const &) = delete;
    MainMenu(MainMenu &&) = delete;
    MainMenu &operator=(MainMenu &) = delete;
    void      initGUI();
    bool      onExitClick(CEGUI::EventArgs const &);
    bool      onPlayClick(CEGUI::EventArgs const &);

    GUI                 m_gui;
    OIS::ParamList      m_param;
    GameState           m_curState;
  };
}

#endif // CPP_INDIE_STUDIO_MAINMENU_HPP_
