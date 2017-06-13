//
// Created by brout_m on 09/06/17.
//

#ifndef MENUKEYMAP_HPP
#define MENUKEYMAP_HPP

#include "game/menu/GUI.hpp"
#include "game/menu/MenuManager.hpp"
#include "game/menu/IMenuLayer.hpp"

namespace core
{
  class MenuKeymap : public IMenuLayer
  {
  public:
    MenuKeymap(menu::MenuManager &menuManager, GUI &gui);
    virtual ~MenuKeymap(){};
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
    bool onBackClick(CEGUI::EventArgs const &);

  private:
    MenuKeymap(MenuKeymap const &) = delete;
    MenuKeymap(MenuKeymap &&) = delete;
    MenuKeymap &       operator=(MenuKeymap const &) = delete;
    MenuKeymap &       operator=(MenuKeymap &&) = delete;
    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);
    bool onPlayer1Click(CEGUI::EventArgs const &);
    bool onPlayer2Click(CEGUI::EventArgs const &);
    bool onPlayer3Click(CEGUI::EventArgs const &);
    bool onPlayer4Click(CEGUI::EventArgs const &);
    void swapButtons(size_t newSelected);

    GUI &              m_gui;
    GameState          m_curState;
    menu::MenuManager &m_menuManager;
    size_t             m_playerSelected;
    CEGUI::Window *    m_buttons[4];
  };
}

#endif // MENUKEYMAP_HPP
