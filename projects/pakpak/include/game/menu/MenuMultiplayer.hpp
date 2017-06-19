//
// Created by brout_m on 09/06/17.
//

#ifndef MENUMULTIPLAYER_HPP
#define MENUMULTIPLAYER_HPP

#include <memory>
#include <network/NetworkGameServer.hpp>
#include "GUI.hpp"
#include "MenuManager.hpp"
#include "IMenuLayer.hpp"
#include "NetworkManager.hpp"

namespace core
{
  class MenuMultiplayer : public IMenuLayer
  {
  public:
    MenuMultiplayer(menu::MenuManager &menuManager, GUI &gui,
                    SoundManager &sound, NetworkManager &net,
                    SettingsPlayer &settings);
    virtual ~MenuMultiplayer()
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
    MenuMultiplayer(MenuMultiplayer const &) = delete;
    MenuMultiplayer(MenuMultiplayer &&) = delete;
    MenuMultiplayer &  operator=(MenuMultiplayer const &) = delete;
    MenuMultiplayer &  operator=(MenuMultiplayer &&) = delete;
    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

    GUI &              m_gui;
    GameState          m_curState;
    menu::MenuManager &m_menuManager;
    SoundManager &     m_sound;
    GameServer         m_selectGameServer;
    NetworkManager &   m_network;
    SettingsPlayer &   m_settings;

    bool onBackClick(CEGUI::EventArgs const &);
    bool onPlayClick(CEGUI::EventArgs const &);

    bool onBackArea(CEGUI::EventArgs const &);
    bool onPlayArea(CEGUI::EventArgs const &);

    bool getServerPos(CEGUI::EventArgs const &);

    void soundPass();
    void soundClick();
  };
}

#endif // MENUMULTIPLAYER_HPP
