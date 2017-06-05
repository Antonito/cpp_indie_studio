#ifndef APPLAUNCHER_HPP_
#define APPLAUNCHER_HPP_

#include <array>
#include <memory>
#include "IContext.hpp"
#include "GameState.hpp"

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
    Ogre::Root *        m_root;
    Ogre::RenderWindow *m_window;
    // Ogre::SceneManager *m_sceneMgr;
    // Ogre::Camera *      m_camera;
    InputListener *m_inputListener;

    static constexpr std::size_t nbContext =
        static_cast<std::size_t>(GameState::NbGameState);

    std::array<std::unique_ptr<IContext>, nbContext> m_contexts;
    IContext *                                       m_currentContext;
    GameState                                        m_gameState;
  };
}

#endif // !APPLAUNCHER_HPP_
