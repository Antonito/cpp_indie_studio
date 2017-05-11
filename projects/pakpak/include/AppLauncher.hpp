#ifndef APPLAUNCHER_H_
#define APPLAUNCHER_H_

#include <memory>
#include <OGRE/Ogre.h>
#include "GameState.hpp"
#include "InputListener.hpp"
#include "IContext.hpp"

namespace core
{
  class AppLauncher
  {
  public:
    AppLauncher();

    ~AppLauncher();

    bool start();

    void createFrameListener();

  private:
    std::unique_ptr<Ogre::Root>         m_root;
    std::unique_ptr<Ogre::RenderWindow> m_window;
    Ogre::SceneManager *                m_sceneMgr;
    std::unique_ptr<Ogre::Camera>       m_camera;
    std::unique_ptr<InputListener>      m_inputListener;

    static constexpr std::size_t nbContext =
        static_cast<std::size_t>(GameState::NbGameState);

    std::array<std::unique_ptr<IContext>, nbContext> m_contexts;
    IContext *                                       m_currentContext;
    GameState                                        m_gameState;
  };
}

#endif // !APPLAUNCHER_H_