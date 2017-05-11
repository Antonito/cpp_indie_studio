#include "InputListener.hpp"

namespace core
{
  InputListener::InputListener(Ogre::RenderWindow *wnd, Ogre::Camera *camera)
      : m_window(wnd), m_camera(camera)
  {
    startOIS();
  }

  InputListener::~InputListener()
  {
    Ogre::WindowEventUtilities::removeWindowEventListener(m_window, this);
    windowClosed(m_window);
  }

  bool InputListener::frameRenderingQueued(const Ogre::FrameEvent &evt)
  {
    if (m_window->isClosed())
      return false;

    mKeyboard->capture();
    mMouse->capture();

    if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
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
    mInputManager = OIS::InputManager::createInputSystem(pl);

    mMouse = static_cast<OIS::Mouse *>(
        mInputManager->createInputObject(OIS::OISMouse, false));

    mKeyboard = static_cast<OIS::Keyboard *>(
        mInputManager->createInputObject(OIS::OISKeyboard, false));

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
    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
  }

  void InputListener::windowClosed(Ogre::RenderWindow *wnd)
  {
    // Delete all Object when the window close
    if (wnd == m_window)
      {
	if (mInputManager)
	  {
	    mInputManager->destroyInputObject(mMouse);
	    mInputManager->destroyInputObject(mKeyboard);

	    OIS::InputManager::destroyInputSystem(mInputManager);
	    mInputManager = 0;
	  }
      }
  }
}
