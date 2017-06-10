//
// Created by brout_m on 09/06/17.
//

#ifndef MENUMULTIPLAYER_HPP
#define MENUMULTIPLAYER_HPP

#include "game/menu/GUI.hpp"
#include "game/menu/MenuManager.hpp"
#include "game/menu/IMenuLayer.hpp"

namespace core
{
  class MenuMultiplayer : public IMenuLayer
  {
  public:
    MenuMultiplayer(menu::MenuManager &menuManager, GUI &gui);
    virtual ~MenuMultiplayer(){};
    void draw();
    void entry();
    void exit();
    void destroy();
    GameState update() const;
    void build();
    bool keyPressed(const OIS::KeyEvent &arg);
    bool mouseMoved(const OIS::MouseEvent &arg);
    bool mousePressed(const OIS::MouseEvent &arg,
                      OIS::MouseButtonID     id);
    bool mouseReleased(const OIS::MouseEvent &arg,
                       OIS::MouseButtonID     id);
    bool keyReleased(const OIS::KeyEvent &arg);


  private:
    MenuMultiplayer(MenuMultiplayer const &) = delete;
    MenuMultiplayer(MenuMultiplayer &&) = delete;
    MenuMultiplayer &operator=(MenuMultiplayer const &) = delete;
    MenuMultiplayer &operator=(MenuMultiplayer &&) = delete;
    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

    GUI                 &m_gui;
    GameState           m_curState;
    menu::MenuManager   &m_menuManager;

    bool onBackClick(CEGUI::EventArgs const &);
    bool onPlayClick(CEGUI::EventArgs const &e);
  };
}

#endif // MENUMULTIPLAYER_HPP
