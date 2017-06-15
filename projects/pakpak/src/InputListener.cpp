#include "pakpak_stdafx.hpp"

namespace core
{
  InputListener::InputListener(Ogre::RenderWindow *wnd)
      : m_window(wnd), m_inputManager(nullptr), m_mouse(nullptr),
        m_keyboard(nullptr), m_physicWorld(nullptr), m_shutdown(false)
  {
    startOIS();
  }

  InputListener::InputListener(InputListener const &that)
      : m_window(that.m_window), m_inputManager(that.m_inputManager),
        m_mouse(that.m_mouse), m_keyboard(that.m_keyboard),
        m_physicWorld(that.m_physicWorld), m_shutdown(that.m_shutdown)
  {
  }

  InputListener::InputListener(InputListener &&that)
      : m_window(std::move(that.m_window)),
        m_inputManager(std::move(that.m_inputManager)),
        m_mouse(std::move(that.m_mouse)),
        m_keyboard(std::move(that.m_keyboard)),
        m_physicWorld(std::move(that.m_physicWorld)),
        m_shutdown(std::move(that.m_shutdown))
  {
  }

  InputListener::~InputListener()
  {
    Ogre::WindowEventUtilities::removeWindowEventListener(m_window, this);
    windowClosed(m_window);
  }

  InputListener &InputListener::operator=(InputListener const &that)
  {
    if (this == &that)
      return (*this);
    m_window = that.m_window;
    m_inputManager = that.m_inputManager;
    m_mouse = that.m_mouse;
    m_keyboard = that.m_keyboard;
    m_physicWorld = that.m_physicWorld;
    m_shutdown = that.m_shutdown;
    return (*this);
  }

  InputListener &InputListener::operator=(InputListener &&that)
  {
    if (this == &that)
      return (*this);
    m_window = std::move(that.m_window);
    m_inputManager = std::move(that.m_inputManager);
    m_mouse = std::move(that.m_mouse);
    m_keyboard = std::move(that.m_keyboard);
    m_physicWorld = std::move(that.m_physicWorld);
    m_shutdown = std::move(that.m_shutdown);
    return (*this);
  }

  bool InputListener::frameRenderingQueued(const Ogre::FrameEvent &)
  {
    if (m_window->isClosed())
      return false;

    m_keyboard->capture();
    m_mouse->capture();

    if (m_shutdown)
      return false;

    return true;
  }

  void InputListener::startOIS()
  {
    Ogre::LogManager::getSingletonPtr()->logMessage(
        "*** Initializing OIS ***");
    // Change logger ?

    // Get the identifier of the RenderWindow
    OIS::ParamList     pl;
    size_t             windowHnd = 0;
    std::ostringstream windowHndStr;

    m_window->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    // Create Input System
    m_inputManager = OIS::InputManager::createInputSystem(pl);

    m_mouse = static_cast<OIS::Mouse *>(
        m_inputManager->createInputObject(OIS::OISMouse, true));

    m_keyboard = static_cast<OIS::Keyboard *>(
        m_inputManager->createInputObject(OIS::OISKeyboard, true));

    // Set the auto Resize
    windowResized(m_window);
    Ogre::WindowEventUtilities::addWindowEventListener(m_window, this);
  }

  void InputListener::setMouseEventCallback(OIS::MouseListener *listener)
  {
    m_mouse->setEventCallback(listener);
  }

  void InputListener::setKeyboardEventCallback(OIS::KeyListener *listener)
  {
    m_keyboard->setEventCallback(listener);
  }

  void InputListener::capture()
  {
    m_keyboard->capture();
    m_mouse->capture();
  }

  void InputListener::shutdown()
  {
    m_shutdown = true;
  }

  bool InputListener::frameStarted(Ogre::FrameEvent const &evt)
  {
    if (m_physicWorld)
      {
	m_physicWorld->stepSimulation(evt.timeSinceLastFrame);
      }
    return (true);
  }

  bool InputListener::frameEnd(Ogre::FrameEvent const &evt)
  {
    if (m_physicWorld)
      {
	m_physicWorld->stepSimulation(evt.timeSinceLastFrame);
      }
    return (true);
  }

  void InputListener::setPhysicWorld(OgreBulletDynamics::DynamicsWorld *world)
  {
    m_physicWorld = world;
  }

  void InputListener::windowResized(Ogre::RenderWindow *wnd)
  {
    // Get the resized window metrics
    std::uint32_t width, height, depth;
    std::int32_t  left, top;

    wnd->getMetrics(width, height, depth, left, top);
    const OIS::MouseState &ms = m_mouse->getMouseState();
    ms.width = static_cast<std::int32_t>(width);
    ms.height = static_cast<std::int32_t>(height);
  }

  void InputListener::windowClosed(Ogre::RenderWindow *wnd)
  {
    // Delete all Object when the window close
    if (wnd == m_window)
      {
	if (m_inputManager)
	  {
	    m_inputManager->destroyInputObject(m_mouse);
	    m_inputManager->destroyInputObject(m_keyboard);

	    OIS::InputManager::destroyInputSystem(m_inputManager);
	    m_inputManager = 0;
	  }
      }
  }
}
