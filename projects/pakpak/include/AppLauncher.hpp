#ifndef APPLAUNCHER_HPP_
#define APPLAUNCHER_HPP_

#include <array>
#include <memory>
#include "IContext.hpp"
#include "GameState.hpp"
#include "SettingsPlayer.hpp"
#include "SoundManager.hpp"

// Disable clang warning for templated class padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

// Forward declaration for faster compilation
namespace Ogre
{
  class Root;
  class RenderWindow;
  class SceneManager;
  class Camera;
}

namespace core
{
  // Forward declaration for faster compilation
  class InputListener;

  class AppLauncher
  {
  public:
    AppLauncher();
    AppLauncher(AppLauncher const &that) = delete;
    AppLauncher(AppLauncher &&that) = delete;
    ~AppLauncher();

    AppLauncher &operator=(AppLauncher const &that) = delete;
    AppLauncher &operator=(AppLauncher &&that) = delete;

    bool start();

    void createFrameListener();

  private:
    Ogre::Root *                 m_root;
    Ogre::RenderWindow *         m_window;
    InputListener *              m_inputListener;
    static constexpr std::size_t nbContext =
        static_cast<std::size_t>(GameState::NbGameState);
    std::array<std::unique_ptr<IContext>, nbContext> m_contexts;
    IContext *     m_currentContext;
    GameState      m_gameState;
    SettingsPlayer m_settings;
    SoundManager   m_soundManager;

    void initOpenAl(char const *);
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !APPLAUNCHER_HPP_
