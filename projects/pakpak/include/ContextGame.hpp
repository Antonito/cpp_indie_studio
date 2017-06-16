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
#endif
#include "AContext.hpp"
#include "LocalPlayer.hpp"

// Disable clang warning for templated class padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

namespace game
{
  class ContextGame final : public core::AContext,
                            public OIS::KeyListener,
                            public OIS::MouseListener
  {
  public:
    ContextGame(Ogre::RenderWindow *win, core::InputListener *input,
                core::SettingsPlayer &);
    ContextGame(ContextGame const &) = delete;
    ContextGame(ContextGame &&) = delete;
    virtual ~ContextGame();

    ContextGame &operator=(ContextGame const &) = delete;
    ContextGame &operator=(ContextGame &&) = delete;

    virtual void enable();
    virtual void disable();

    void updateViewPort();

    virtual core::GameState update();
    virtual void            display();
    bool keyPressed(const OIS::KeyEvent &arg);

    bool keyReleased(const OIS::KeyEvent &arg);

    bool mouseMoved(const OIS::MouseEvent &arg);

    bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

    bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

  private:
    GameData                                  m_game;
    std::vector<std::unique_ptr<LocalPlayer>> m_players;
    core::SettingsPlayer &                    m_settings;
    bool                                      m_quit;
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !CONTEXTGAME_HPP_
