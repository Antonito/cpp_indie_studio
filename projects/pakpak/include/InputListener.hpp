#ifndef INPUTLISTENER_H_
#define INPUTLISTENER_H_

#include <memory>
#include <OGRE/Ogre.h>
#include <OIS/OISInputManager.h>
#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>

namespace core
{
  class InputListener : public Ogre::FrameListener,
                        public Ogre::WindowEventListener
  {
  public:
    InputListener() = delete;
    InputListener(Ogre::RenderWindow *wnd);
    InputListener(InputListener const &that);
    InputListener(InputListener &&that);
    virtual ~InputListener();

    InputListener &operator=(InputListener const &that);
    InputListener &operator=(InputListener &&that);

    virtual void windowResized(Ogre::RenderWindow *rw);
    virtual void windowClosed(Ogre::RenderWindow *rw);
    bool         frameRenderingQueued(const Ogre::FrameEvent &evt);
    void         startOIS();

    void setMouseEventCallback(OIS::MouseListener *listener);
    void setKeyboardEventCallback(OIS::KeyListener *listener);

    void shutdown();

  private:
    Ogre::RenderWindow *m_window;
    OIS::InputManager * m_inputManager;
    OIS::Mouse *        m_mouse;
    OIS::Keyboard *     m_keyboard;
    bool                m_shutdown;
  };
}

#endif // !INPUTLISTENER_H_
