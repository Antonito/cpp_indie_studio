#include "pakpak_stdafx.hpp"

namespace splash
{
  ContextSplash::ContextSplash(Ogre::RenderWindow * win,
                               core::InputListener *input,
                               core::SoundManager & sound)
      : core::AContext(win, input),
        // Create the scene manager
        m_sceneMgr(Ogre::Root::getSingleton().createSceneManager(
            "DefaultSceneManager", "Splash scene manager")),
        // Create the entity
        m_entity(m_sceneMgr->createEntity("Jeep_default.mesh")),
        // Create the node
        m_node(m_sceneMgr->getRootSceneNode()->createChildSceneNode()),
        // Create the main light
        m_light(m_sceneMgr->createLight("MainLight")),
        // Create the camera
        m_camera(m_sceneMgr->createCamera("MainCamera")), m_viewport(nullptr),
        m_sound(sound), m_start(clock_t::now())
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
    m_sound.playSound(core::ESound::SPLASH_SONG);
    nope::log::Log(Debug) << "Splash context enabled";
    m_viewport = m_win->addViewport(m_camera);

    m_viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

    m_camera->setAspectRatio(Ogre::Real(m_viewport->getActualWidth()) /
                             Ogre::Real(m_viewport->getActualHeight()));
  }

  void ContextSplash::disable()
  {
    m_sound.stopSound(core::ESound::SPLASH_SONG);
    nope::log::Log(Debug) << "Splash context disabled";
    m_win->removeAllViewports();
  }

  core::GameState ContextSplash::update()
  {
    std::chrono::milliseconds t =
        std::chrono::duration_cast<std::chrono::milliseconds>(clock_t::now() -
                                                              m_start);
    constexpr std::int32_t max = 0;

    if (t.count() < max)
      {
	m_camera->setPosition(0, 0, Ogre::Real(100 + max - t.count()));
	return (core::GameState::Splash);
      }
    else
      return (core::GameState::Menu);
  }

  void ContextSplash::display()
  {
  }
}
