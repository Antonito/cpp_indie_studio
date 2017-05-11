#include "InputListener.hpp"

namespace core
{
  InputListener::InputListener(Ogre::RenderWindow *wnd, Ogre::Camera *camera)
      : m_window(wnd), m_camera(camera), m_inputManager(nullptr),
        m_mouse(nullptr), m_keyboard(nullptr)
  {
    startOIS();
  }

  InputListener::InputListener(InputListener const &that)
      : m_window(that.m_window), m_camera(that.m_camera),
        m_inputManager(that.m_inputManager), m_mouse(that.m_mouse),
        m_keyboard(that.m_keyboard)
  {
  }

  InputListener::InputListener(InputListener &&that)
      : m_window(std::move(that.m_window)), m_camera(std::move(that.m_camera)),
        m_inputManager(std::move(that.m_inputManager)),
        m_mouse(std::move(that.m_mouse)),
        m_keyboard(std::move(that.m_keyboard))
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
    m_camera = that.m_camera;
    m_inputManager = that.m_inputManager;
    m_mouse = that.m_mouse;
    m_keyboard = that.m_keyboard;
    return (*this);
  }

  InputListener &InputListener::operator=(InputListener &&that)
  {
    if (this == &that)
      return (*this);
    m_window = std::move(that.m_window);
    m_camera = std::move(that.m_camera);
    m_inputManager = std::move(that.m_inputManager);
    m_mouse = std::move(that.m_mouse);
    m_keyboard = std::move(that.m_keyboard);
    return (*this);
  }

  bool InputListener::frameRenderingQueued(const Ogre::FrameEvent &evt)
  {
    if (m_window->isClosed())
      return false;

    m_keyboard->capture();
    m_mouse->capture();

    if (m_keyboard->isKeyDown(OIS::KC_ESCAPE))
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
        m_inputManager->createInputObject(OIS::OISMouse, false));

    m_keyboard = static_cast<OIS::Keyboard *>(
        m_inputManager->createInputObject(OIS::OISKeyboard, false));

    // Set the auto Resize
    windowResized(m_window);
    Ogre::WindowEventUtilities::addWindowEventListener(m_window, this);
  }

  void InputListener::windowResized(Ogre::RenderWindow *wnd)
  {
    // Get the resized window metrics
    unsigned int width, height, depth;
    int          left, top;

    wnd->getMetrics(width, height, depth, left, top);
    const OIS::MouseState &ms = m_mouse->getMouseState();
    ms.width = width;
    ms.height = height;
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
