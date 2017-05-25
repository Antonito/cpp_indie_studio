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
    void draw();
    void entry();
    void exit();
    void destroy();

    GameState update() const;

    void build();

  private:
    void initGUI();
    bool onExitClick(CEGUI::EventArgs const &);
    bool onPlayClick(CEGUI::EventArgs const &);

    GUI          m_gui;
    GameState    m_curState;
    Ogre::Camera m_camera;
  };
}

#endif // CPP_INDIE_STUDIO_MAINMENU_HPP_
