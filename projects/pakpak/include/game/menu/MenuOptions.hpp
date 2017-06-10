//
// Created by brout_m on 09/06/17.
//

#ifndef MENUOPTIONS_HPP
#define MENUOPTIONS_HPP

#include "game/menu/GUI.hpp"
#include "game/menu/MenuManager.hpp"
#include "game/menu/IMenuLayer.hpp"

namespace core
{
  class MenuOptions : public IMenuLayer
  {
  public:
    MenuOptions(menu::MenuManager &menuManager, GUI &gui);
    virtual ~MenuOptions(){};
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
    MenuOptions(MenuOptions const &) = delete;
    MenuOptions(MenuOptions &&) = delete;
    MenuOptions &operator=(MenuOptions const &) = delete;
    MenuOptions &operator=(MenuOptions &&) = delete;
    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

    GUI                 &m_gui;
    GameState           m_curState;
    menu::MenuManager   &m_menuManager;

    bool onKeymapEdit(CEGUI::EventArgs const &);
    bool onBackClick(CEGUI::EventArgs const &);
  };
}

#endif // MENUOPTIONS_HPP
