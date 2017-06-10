//
// Created by duhieu_b on 31/05/17.
//

#ifndef CPP_INDIE_STUDIO_MENUMANAGER_HPP
#define CPP_INDIE_STUDIO_MENUMANAGER_HPP

#include <OGRE/Ogre.h>
#include <OIS/OIS.h>
#include "FastStack.hpp"
#include "IMenuLayer.hpp"
#include "IEventHandler.hpp"
#include "ILayerStack.hpp"
#include "InputListener.hpp"

namespace menu
{
  class MenuManager : public game::IEventHandler
  {
  public:
    MenuManager(Ogre::RenderWindow *);
    MenuManager(MenuManager const &) = delete;
    MenuManager(MenuManager &&) = delete;
    virtual ~MenuManager()
    {
    }

    MenuManager &operator=(MenuManager &) = delete;
    MenuManager &operator=(MenuManager &&) = delete;
    bool keyPressed(OIS::KeyEvent const &ke);
    bool keyReleased(OIS::KeyEvent const &ke);
    bool mouseMoved(OIS::MouseEvent const &me);
    bool mousePressed(OIS::MouseEvent const &me, OIS::MouseButtonID id);
    bool mouseReleased(OIS::MouseEvent const &me, OIS::MouseButtonID id);
    void push(core::MenuState);
    void popLayer();
    void begin();
    void end();
    core::IMenuLayer *getMenuLayer();

  private:
    Ogre::SceneManager *m_sceneMan;
    Ogre::Camera *      m_camera;
    Ogre::Viewport *    m_viewport;
    core::GUI           m_gui;

    static constexpr size_t nbContext =
        static_cast<size_t>(core::MenuState::NbMenuState);
    std::array<std::unique_ptr<core::IMenuLayer>, nbContext> m_menuLayer;
    core::FastStack<core::IMenuLayer *> m_layers;
  };
}

#endif // CPP_INDIE_STUDIO_MENUMANAGER_HPP
