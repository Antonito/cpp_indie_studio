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
    InputListener() = delete;
    InputListener(Ogre::RenderWindow *wnd, Ogre::Camera *camera);
    InputListener(InputListener const &that);
    InputListener(InputListener &&that);
    virtual ~InputListener();

    InputListener &operator=(InputListener const &that);
    InputListener &operator=(InputListener &&that);

    virtual void windowResized(Ogre::RenderWindow *rw);
    virtual void windowClosed(Ogre::RenderWindow *rw);
    bool         frameRenderingQueued(const Ogre::FrameEvent &evt);
    void         startOIS();

  private:
    Ogre::RenderWindow *m_window;
    Ogre::Camera *      m_camera;
    OIS::InputManager * m_inputManager;
    OIS::Mouse *        m_mouse;
    OIS::Keyboard *     m_keyboard;
  };
}

#endif // !INPUTLISTENER_H_
