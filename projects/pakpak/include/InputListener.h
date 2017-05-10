#ifndef INPUTLISTENER_H_
#define INPUTLISTENER_H_

#include <OGRE/Ogre.h>
#include <memory>
#include <OIS/OIS.h>

namespace core
{
  class InputListener : public Ogre::FrameListener,
                        public Ogre::WindowEventListener
  {
  public:
    InputListener(Ogre::RenderWindow *wnd, Ogre::Camera *camera);
    virtual ~InputListener();
    virtual void windowResized(Ogre::RenderWindow *rw);
    virtual void windowClosed(Ogre::RenderWindow *rw);
    bool         frameRenderingQueued(const Ogre::FrameEvent &evt);
    void         startOIS();

  private:
    Ogre::RenderWindow *mWindow;
    Ogre::Camera *      mCamera;
    OIS::InputManager * mInputManager;
    OIS::Mouse *        mMouse;
    OIS::Keyboard *     mKeyboard;
  };
}

#endif // !INPUTLISTENER_H_
