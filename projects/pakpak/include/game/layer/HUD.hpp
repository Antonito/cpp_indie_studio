//
// Created by brout_m on 14/06/17.
//

#ifndef CPP_INDIE_STUDIO_HUD_HPP
#define CPP_INDIE_STUDIO_HUD_HPP

#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <OIS/OISPrereqs.h>
#include <map>
#include <OIS/OIS.h>

namespace core
{
  class HUD
  {
  public:
    HUD();
    ~HUD();
    HUD &operator=(HUD const &) = delete;
    HUD &operator=(HUD &&) = delete;
    HUD(HUD const &) = delete;
    HUD(HUD &&) = delete;
    void           initHUD();
    void           destroyHUD();
    void           loadScheme(const std::string &);
    void           loadLayout(const std::string &);
    void           addLayout(const std::string &);
    void           removeLayout(const std::string &);
    void           grabMouse();
    void           showCursor(bool);
    void           hideCursor(bool);
    CEGUI::Window *getChild(const std::string &);
    CEGUI::Window *operator[](CEGUI::Vector2f &);
    CEGUI::Window *getRoot();
    void           setQuit(bool);
    bool           getQuit() const;

  private:
    CEGUI::OgreRenderer *m_renderer;
    CEGUI::Window *      m_rootWindow;
    CEGUI::GUIContext *  m_context;
    OIS::ParamList       m_param;
    std::map<std::string, CEGUI::Window *> m_windows;
    bool m_quit;
  };
}

#endif // CPP_INDIE_STUDIO_HUD_HPP
