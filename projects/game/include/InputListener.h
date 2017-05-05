#ifndef INPUTLISTENER_H_
#define INPUTLISTENER_H_

#include <Ogre.h>
#include <memory>
#include <OIS/OIS.h>

class InputListener : public Ogre::FrameListener,
                      public Ogre::WindowEventListener
{
public:
  virtual void windowResized(Ogre::RenderWindow *rw);
  virtual void windowClosed(Ogre::RenderWindow *rw);

private:
  std::unique_ptr<Ogre::RenderWindow> mWindow;
  std::unique_ptr<Ogre::Camera>       mCamera;
  std::unique_ptr<OIS::InputManager>  mInputManager;
  std::unique_ptr<OIS::Mouse>         mMouse;
  std::unique_ptr<OIS::Keyboard>      mKeyboard;
};

#endif // !INPUTLISTENER_H_
