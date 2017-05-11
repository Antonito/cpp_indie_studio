#ifndef APPLAUNCHER_HPP_
#define APPLAUNCHER_HPP_

#include <memory>

#if defined(_WIN32) && !defined(__on__linux__)
#include <OgreRenderWindow.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreLight.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#endif

#if defined(__on__linux__) && !defined(_WIN32)
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreLight.h>
#include <OGRE/OgreCamera.h>
#include <OGRE/OgreViewport.h>
#endif

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
    Ogre::SceneManager *m_sceneMgr;
    Ogre::Camera *      m_camera;
    InputListener *     m_inputListener;

    static constexpr std::size_t nbContext =
        static_cast<std::size_t>(GameState::NbGameState);

    std::array<std::unique_ptr<IContext>, nbContext> m_contexts;
    IContext *                                       m_currentContext;
    GameState                                        m_gameState;
  };
}

#endif // !APPLAUNCHER_HPP_