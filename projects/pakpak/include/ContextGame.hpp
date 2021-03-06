#ifndef CONTEXTGAME_HPP_
#define CONTEXTGAME_HPP_

#include <vector>
#include <memory>
#include <OGRE/OgreRenderWindow.h>
#if defined __APPLE__
#include <ois/OISMouse.h>
#include <ois/OISKeyboard.h>
#else
#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>
#include <game/Timer.hpp>

#endif

#include "HUD.hpp"
#include "Ai.hpp"
#include "AContext.hpp"
#include "EmptyCar.hpp"
#include "Timer.hpp"

// Disable clang warning for templated class padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

namespace game
{
  class LocalPlayer;
  class ContextGame final : public core::AContext,
                            public OIS::KeyListener,
                            public OIS::MouseListener
  {
  public:
    ContextGame(Ogre::RenderWindow *win, core::InputListener *input,
                core::SettingsPlayer &, core::NetworkManager &,
                core::SoundManager &);
    virtual ~ContextGame();
    ContextGame &operator=(ContextGame const &) = delete;
    ContextGame &operator=(ContextGame &&) = delete;
    ContextGame(ContextGame const &) = delete;
    ContextGame(ContextGame &&) = delete;
    virtual void            enable();
    virtual void            disable();
    void                    updateViewPort();
    virtual core::GameState update();
    virtual void            display();
    bool                    keyPressed(const OIS::KeyEvent &arg);
    bool                    keyReleased(const OIS::KeyEvent &arg);
    bool                    mouseMoved(const OIS::MouseEvent &arg);
    bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    void setQuit(bool);

  private:
    GameData                                  m_game;
    std::vector<std::unique_ptr<LocalPlayer>> m_players;
    std::vector<std::unique_ptr<Ai>>          m_ia;
    core::SettingsPlayer &                    m_settings;
    bool                                      m_quit;
    std::unique_ptr<core::HUD>                m_hud;
    core::NetworkManager &                    m_net;
    core::SoundManager &                      m_sound;
    game::Timer                               m_timer;
    game::Timer                               m_iaTimer;
    bool                                      m_gameStart;
    std::vector<GameClientToGSPacketUDP>      m_networkPacket;

    void setUDPPacket(GameClientToGSPacketUDP &packet, LocalPlayer &player);
    void setUDPPacketDirection(GameClientToGSPacketUDP &,
                               Ogre::Quaternion const &);
    void setUDPPatcketPosition(GameClientToGSPacketUDP &,
                               Ogre::Vector3 const &);
    void setPlayersFromUDPPackets();
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !CONTEXTGAME_HPP_
