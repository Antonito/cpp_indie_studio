#ifndef LOCALPLAYER_HPP_
#define LOCALPLAYER_HPP_

#include <cstdint>
#include <array>
#include <memory>
#include <utility>
#include <OGRE/OgreCamera.h>
#include <OGRE/OgreViewport.h>
#include "GameData.hpp"
#include "PlayerData.hpp"
#include "CameraMode.hpp"
#include "GameLayer.hpp"
#include "FastStack.hpp"
#include "IEventHandler.hpp"
#include "ILayerStack.hpp"
#include "ACar.hpp"
#include "ILayer.hpp"
#include "SettingsPlayer.hpp"

// Disable clang warning for templated class padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

namespace game
{
  class ContextGame;

  class LocalPlayer final : public IEventHandler, public ILayerStack
  {
  public:
    LocalPlayer() = delete;
    LocalPlayer(Ogre::RenderWindow *, GameData &, PlayerData *, int,
                core::SettingsPlayer &, core::HUD *, game::ContextGame &,
                std::vector<std::unique_ptr<LocalPlayer>> &, std::uint8_t);
    LocalPlayer(LocalPlayer const &) = delete;
    LocalPlayer(LocalPlayer &&);
    virtual ~LocalPlayer();

    LocalPlayer &operator=(LocalPlayer const &) = delete;
    LocalPlayer &operator=(LocalPlayer &&) = delete;

    virtual bool keyPressed(OIS::KeyEvent const &ke);
    virtual bool keyReleased(OIS::KeyEvent const &ke);

    virtual bool mouseMoved(OIS::MouseEvent const &me);
    virtual bool mousePressed(OIS::MouseEvent const &me,
                              OIS::MouseButtonID     id);
    virtual bool mouseReleased(OIS::MouseEvent const &me,
                               OIS::MouseButtonID     id);

    virtual void push(GameLayer layer);
    virtual void          popLayer();
    virtual std::uint32_t getSpeed() const;
    virtual std::uint32_t getPosition() const;

    void setViewPort(Ogre::Real left, Ogre::Real top, Ogre::Real width,
                     Ogre::Real height);
    void display();
    void crossFinishLine(
        std::chrono::time_point<std::chrono::high_resolution_clock> finishTime,
        int                                                         nbRounds);

    ACar &      car();
    ACar const &car() const;

    int  order() const;
    void order(int);

    std::pair<void (LocalPlayer::*)(), void (LocalPlayer::*)()> &
                          actions(std::string const &);
    core::SettingsPlayer &settings();

    std::size_t getRank() const;

    bool getFinished() const;

  private:
    void setActionMap();

    void speedUp();
    void slowDown();
    void turnLeft();
    void turnRight();
    void useObject();
    void changeView();
    void displayMap();
    void openChat();
    void openMenu();

    void speedUpReleased();
    void slowDownReleased();
    void turnLeftReleased();
    void turnRightReleased();
    void useObjectReleased();
    void changeViewReleased();
    void displayMapReleased();
    void openChatReleased();
    void openMenuReleased();

    PlayerData *                 m_data;
    CameraMode                   m_cameraMode;
    static constexpr std::size_t nbLayer =
        static_cast<std::size_t>(GameLayer::NbLayer);
    std::array<std::unique_ptr<ILayer>, nbLayer> m_layers;
    core::FastStack<ILayer *> m_currentLayers;
    Ogre::Camera *            m_cam;
    Ogre::Viewport *          m_viewport;
    std::vector<std::chrono::time_point<std::chrono::high_resolution_clock>>
                          m_rounds;
    core::SettingsPlayer &m_settings;
    std::map<std::string,
             std::pair<void (LocalPlayer::*)(), void (LocalPlayer::*)()>>
                        m_actions;
    Ogre::RenderWindow *m_win;
    int                 m_order;
    core::HUD *         m_hud;
    game::ContextGame & m_contextGame;
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !LOCALPLAYER_HPP_
