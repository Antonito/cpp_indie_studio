//
// Created by duhieu_b on 23/05/17.
//

#ifndef CPP_INDIE_STUDIO_MGUI_HPP_
#define CPP_INDIE_STUDIO_MGUI_HPP_

#include <iostream>
#include <OGRE/Ogre.h>
#include <OIS/OIS.h>
#include <glm/glm.hpp>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

namespace core
{
  class GUI
  {
  public:
    ~GUI();
    GUI();
    void init();
    void destroy();
    void draw();
    void setFont(std::string const &);
    CEGUI::Window *createButton(CEGUI::Window *, std::string const &,
                                glm::vec4 const &, glm::vec4 const &,
                                std::string const &);
    CEGUI::Window *createButton(std::string const &, glm::vec4 const &,
                                glm::vec4 const &, std::string const &);
    void setPos(CEGUI::Window *, glm::vec4 const &, glm::vec4 const &);
    void loadSheme(std::string const &);
    void loadLayout(std::string const &);
    CEGUI::OgreRenderer *getRender() const;
    CEGUI::GUIContext *getContext() const;
    CEGUI::Window *getRoot() const;
    void hideCursor(bool disable = true);
    void setCursorArrow(std::string const &);

  private:
    CEGUI::OgreRenderer *m_renderer;
    CEGUI::Window *      m_root;
    CEGUI::GUIContext *  m_context;
    OIS::ParamList      m_param;

    GUI(GUI const &) = delete;
    GUI &operator=(GUI const &) = delete;
  };
}

#endif // CPP_INDIE_STUDIO_GUI_HPP_