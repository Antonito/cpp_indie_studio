//
// Created by brout_m on 09/06/17.
//

#ifndef MENUSOLO_HPP
#define MENUSOLO_HPP

#include "GUI.hpp"
#include "MenuManager.hpp"
#include "IMenuLayer.hpp"

namespace core
{
  class MenuSolo : public IMenuLayer
  {
  public:
    MenuSolo(menu::MenuManager &menuManager, GUI &gui);
    virtual ~MenuSolo(){};
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
    MenuSolo(MenuSolo const &) = delete;
    MenuSolo(MenuSolo &&) = delete;
    MenuSolo &         operator=(MenuSolo const &) = delete;
    MenuSolo &         operator=(MenuSolo &&) = delete;
    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

    GUI &              m_gui;
    GameState          m_curState;
    menu::MenuManager &m_menuManager;

    bool onBackClick(CEGUI::EventArgs const &);
    bool onPlayClick(CEGUI::EventArgs const &e);
    bool onEasyClick(CEGUI::EventArgs const &e);
    bool onHardClick(CEGUI::EventArgs const &e);
  };
}

#endif // MENUSOLO_HPP
