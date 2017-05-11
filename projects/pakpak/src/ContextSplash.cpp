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
        m_camera(m_sceneMgr->createCamera("MainCamera")), m_viewport(nullptr)
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
    return (core::GameState::Splash);
  }

  void ContextSplash::display()
  {
  }
}