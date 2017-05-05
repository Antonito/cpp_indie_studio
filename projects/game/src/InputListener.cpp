#include "InputListener.h"

InputListener(std::unique_ptr<Ogre::RenderWindow> wnd,
              std::unique_ptr<Ogre::Camera>       camera)
{
  mWindow = wnd;
  mCamera = camera;
  startOIS();
}

InputListener::~InputListener()
{
  Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
  windowClosed(mWindow);
}

bool InputListener::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
  if (mWindow->isClosed())
    return false;

  mKeyboard->capture();
  mMouse->capture();

  if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
    return false;

  return true;
}

void InputListener::startOIS()
{
  Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
  // Change logger ?

  // Get the identifier of the RenderWindow
  OIS::ParamList     pl;
  size_t             windowHnd = 0;
  std::ostringstream windowHndStr;

  mWindow->getCustomAttribute("WINDOW", &windowHnd);
  windowHndStr << windowHnd;
  pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

  // Create Input System
  mInputManager =
      std::unique<OIS::InputManager>(OIS::InputManager::createInputSystem(pl));

  mMouse = std::unique<OIS::Mouse>(static_cast<OIS::Mouse *>(
      mInputManager->createInputObject(OIS::OISMouse, false)));

  mKeyboard = std::unique<OIS::Keyboard>(static_cast<OIS::Keyboard *>(
      mInputManager->createInputObject(OIS::OISKeyboard, false)));

  // Set the auto Resize
  windowResized(mWindow);
  Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
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
  if (wnd == mWindow)
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
