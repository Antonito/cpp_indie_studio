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

#if defined(__linux__)
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreLight.h>
#include <OGRE/OgreCamera.h>
#include <OGRE/OgreViewport.h>
#endif

#include "ContextSplash.hpp"
#include "GameState.hpp"

namespace splash
{
  ContextSplash::ContextSplash(Ogre::RenderWindow * win,
                               core::InputListener *input)
      : core::AContext(win, input),
        // Create the scene manager
        m_sceneMgr(Ogre::Root::getSingleton().createSceneManager(
            "DefaultSceneManager", "Splash scene manager")),
        // Create the entity
        m_entity(m_sceneMgr->createEntity("ogrehead.mesh")),
        // Create the node
        m_node(m_sceneMgr->getRootSceneNode()->createChildSceneNode()),
        // Create the main light
        m_light(m_sceneMgr->createLight("MainLight")),
        // Create the camera
        m_camera(m_sceneMgr->createCamera("MainCamera")), m_viewport(nullptr),
        m_start(clock_t::now())
  {
    // Set the ambiant light
    m_sceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    m_node->attachObject(m_entity);
    m_light->setPosition(20, 80, 50);

    m_camera->setPosition(0, 0, 100);
    m_camera->lookAt(0, 0, 0);

    m_camera->setNearClipDistance(3);
  }

  ContextSplash::~ContextSplash()
  {
  }

  void ContextSplash::enable()
  {
    m_viewport = m_win->addViewport(m_camera);

    m_viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

    m_camera->setAspectRatio(Ogre::Real(m_viewport->getActualWidth()) /
                             Ogre::Real(m_viewport->getActualHeight()));
  }

  void ContextSplash::disable()
  {
    m_win->removeAllViewports();
  }

  core::GameState ContextSplash::update()
  {
    std::chrono::milliseconds t =
        std::chrono::duration_cast<std::chrono::milliseconds>(clock_t::now() -
                                                              m_start);
    constexpr std::int32_t max = 3000;

    if (t.count() < max)
      {
	m_camera->setPosition(0, 0, 100 + max - t.count());
	return (core::GameState::Splash);
      }
    else
      return (core::GameState::Menu);
  }

  void ContextSplash::display()
  {
  }
}