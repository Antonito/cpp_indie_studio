#ifndef INPUTLISTENER_H_
#define INPUTLISTENER_H_

#include <memory>
#include <OGRE/Ogre.h>
#include <OIS/OISInputManager.h>
#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>

// Disable clang warning for templated class padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang            system_header
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC            system_header
#endif

#include <OgreBulletDynamicsWorld.h>

// Enable clang warning for templated class padding
#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

namespace core
{
  class InputListener : public Ogre::FrameListener,
                        public Ogre::WindowEventListener
  {
  public:
    InputListener() = delete;
    explicit InputListener(Ogre::RenderWindow *wnd);
    InputListener(InputListener const &that);
    InputListener(InputListener &&that);
    virtual ~InputListener();

    InputListener &operator=(InputListener const &that);
    InputListener &operator=(InputListener &&that);

    virtual void windowResized(Ogre::RenderWindow *rw);
    virtual void windowClosed(Ogre::RenderWindow *rw);
    bool frameRenderingQueued(const Ogre::FrameEvent &evt);
    void startOIS();

    void setMouseEventCallback(OIS::MouseListener *listener);
    void setKeyboardEventCallback(OIS::KeyListener *listener);

    void capture();
    void shutdown();

    bool frameStarted(Ogre::FrameEvent const &evt);
    bool frameEnd(Ogre::FrameEvent const &evt);

    void setPhysicWorld(OgreBulletDynamics::DynamicsWorld *world);

  private:
    Ogre::RenderWindow *m_window;
    OIS::InputManager * m_inputManager;
    OIS::Mouse *        m_mouse;
    OIS::Keyboard *     m_keyboard;

    OgreBulletDynamics::DynamicsWorld *m_physicWorld;

    bool m_shutdown;
  };
}

#endif // !INPUTLISTENER_H_
