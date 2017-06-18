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
    MenuSolo(menu::MenuManager &menuManager, GUI &gui, SoundManager &sound);
    virtual ~MenuSolo()
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

  private:
    MenuSolo(MenuSolo const &) = delete;
    MenuSolo(MenuSolo &&) = delete;
    MenuSolo &         operator=(MenuSolo const &) = delete;
    MenuSolo &         operator=(MenuSolo &&) = delete;
    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

    GUI &              m_gui;
    GameState          m_curState;
    menu::MenuManager &m_menuManager;
    SoundManager &     m_sound;
    size_t             m_playerCount;

    bool onBackClick(CEGUI::EventArgs const &);
    bool onPlayClick(CEGUI::EventArgs const &);
    bool onEasyClick(CEGUI::EventArgs const &);
    bool onHardClick(CEGUI::EventArgs const &);
    bool onPlayersClick(CEGUI::EventArgs const &);
    bool onArea(CEGUI::EventArgs const &);

    void soundPass();
    void soundClick();
    void setButtonText(std::string const &buttonName);
  };
}

#endif // MENUSOLO_HPP
