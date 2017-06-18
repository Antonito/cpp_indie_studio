//
// Created by duhieu_b on 23/05/17.
//

#ifndef CPP_INDIE_STUDIO_MGUI_HPP_
#define CPP_INDIE_STUDIO_MGUI_HPP_

#include <iostream>
#include <OGRE/Ogre.h>
#if defined __APPLE__
#include <ois/OIS.h>
#else
#include <OIS/OIS.h>
#endif
#include <glm/glm.hpp>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include "menu/AssetResizer.hpp"

namespace core
{
  class GUI
  {
  public:
    ~GUI();
    GUI(Ogre::RenderWindow *win);
    void           init();
    void           destroy();
    void           draw();
    void           setFont(std::string const &);
    CEGUI::Window *createButton(CEGUI::Window *, std::string const &,
                                glm::vec4 const &, glm::vec4 const &,
                                std::string const &);
    CEGUI::Window *createButton(std::string const &, glm::vec4 const &,
                                glm::vec4 const &, std::string const &);
    void setPos(CEGUI::Window *, glm::vec4 const &, glm::vec4 const &);
    void loadSheme(std::string const &);
    void loadLayout(std::string const &);
    void update();
    CEGUI::OgreRenderer *getRender() const;
    CEGUI::GUIContext *  getContext() const;
    CEGUI::Window *      getRoot() const;
    void hideCursor(bool disable = true);
    void setCursorArrow(std::string const &);
    void removeLayout(const std::string &layout);
    void addLayout(const std::string &layout);


  private:
    CEGUI::OgreRenderer *m_renderer;
    CEGUI::Window *      m_root;
    CEGUI::GUIContext *  m_context;
    OIS::ParamList       m_param;
    Ogre::RenderWindow * m_win;
    std::map<std::string, CEGUI::Window *> m_windows;

    GUI(GUI const &) = delete;
    GUI &operator=(GUI const &) = delete;
  };
}

#endif // CPP_INDIE_STUDIO_GUI_HPP_
