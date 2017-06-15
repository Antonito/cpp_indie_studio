//
// Created by brout_m on 09/06/17.
//

#ifndef MENUKEYMAP_HPP
#define MENUKEYMAP_HPP

#include "GUI.hpp"
#include "MenuManager.hpp"
#include "IMenuLayer.hpp"
#include "SettingsPlayer.hpp"

namespace core
{
  class MenuKeymap : public IMenuLayer
  {
  public:
    MenuKeymap(menu::MenuManager &menuManager, GUI &gui,
               SettingsPlayer &settings);
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
    bool onUpClick(CEGUI::EventArgs const &);
    bool onDownClick(CEGUI::EventArgs const &);
    bool onLeftClick(CEGUI::EventArgs const &);
    bool onRightClick(CEGUI::EventArgs const &);
    bool onUseClick(CEGUI::EventArgs const &);
    bool onPauseClick(CEGUI::EventArgs const &);

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
    SettingsPlayer &   m_settings;
    bool               m_listening;
    OIS::KeyCode &     m_curKey;
    std::string        m_curButton;
  };
}

#endif // MENUKEYMAP_HPP
