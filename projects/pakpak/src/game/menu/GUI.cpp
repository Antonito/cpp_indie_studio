//
// Created by duhieu_b on 23/05/17.
//

#include "pakpak_stdafx.hpp"

namespace core
{
  GUI::GUI(Ogre::RenderWindow *win)
      : m_renderer(nullptr), m_root(nullptr), m_context(nullptr), m_param(),
        m_win(win), m_windows({})
  {
    init();
  }

  void GUI::init()
  {
    nope::log::Log(Debug) << "Ogre::Root::singletonPtr : "
                          << Ogre::Root::getSingletonPtr();
    m_renderer = &CEGUI::OgreRenderer::bootstrapSystem();
    nope::log::Log(Debug) << "Ogre::Root::singletonPtr : "
                          << Ogre::Root::getSingletonPtr();
    CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
    m_context = &CEGUI::System::getSingleton().getDefaultGUIContext();
    loadSheme("TaharezLook.scheme");
  }

  void GUI::destroy()
  {
    CEGUI::WindowManager::getSingleton().destroyWindow(m_root);
    m_root = nullptr;
  }

  void GUI::setFont(std::string const &p_font)
  {
    CEGUI::FontManager::getSingleton().createFromFile(p_font + ".font");
    m_context->setDefaultFont(p_font);
  }

  CEGUI::Window *GUI::createButton(CEGUI::Window *    p_win,
                                   std::string const &p_type,
                                   glm::vec4 const &  p_dim1,
                                   glm::vec4 const &  p_dim2,
                                   std::string const &p_name = "")
  {
    CEGUI::Window *p_newWin =
        CEGUI::WindowManager::getSingleton().createWindow(p_type, p_name);
    p_win->addChild(p_newWin);
    setPos(p_newWin, p_dim1, p_dim2);
    return p_newWin;
  }

  CEGUI::Window *GUI::createButton(std::string const &p_type,
                                   glm::vec4 const &  p_dim1,
                                   glm::vec4 const &  p_dim2,
                                   std::string const &p_name = "")
  {
    CEGUI::Window *p_newWin =
        CEGUI::WindowManager::getSingleton().createWindow(p_type, p_name);
    m_root->addChild(p_newWin);
    setPos(p_newWin, p_dim1, p_dim2);
    return p_newWin;
  }

  void GUI::setPos(CEGUI::Window *p_win, glm::vec4 const &p_dim1,
                   glm::vec4 const &p_dim2)
  {
    p_win->setPosition(CEGUI::UVector2(CEGUI::UDim(p_dim1.x, p_dim2.x),
                                       CEGUI::UDim(p_dim1.y, p_dim2.y)));
    p_win->setSize(CEGUI::USize(CEGUI::UDim(p_dim1.z, p_dim2.z),
                                CEGUI::UDim(p_dim1.w, p_dim2.w)));
  }

  CEGUI::OgreRenderer *GUI::getRender() const
  {
    return m_renderer;
  }

  CEGUI::GUIContext *GUI::getContext() const
  {
    return m_context;
  }

  GUI::~GUI()
  {
  }

  void GUI::update()
  {
    CEGUI::Size<float> sizef;
    sizef.d_height = static_cast<float>(m_win->getHeight());
    sizef.d_width = static_cast<float>(m_win->getWidth());

    m_renderer->setDisplaySize(sizef);
  }

  void GUI::draw()
  {
  }

  void GUI::loadSheme(std::string const &p_shem)
  {
    CEGUI::SchemeManager::getSingleton().createFromFile(p_shem);
  }

  void GUI::hideCursor(bool disable)
  {
    if (!disable)
      CEGUI::System::getSingleton()
          .getDefaultGUIContext()
          .getMouseCursor()
          .show();
    else
      CEGUI::System::getSingleton()
          .getDefaultGUIContext()
          .getMouseCursor()
          .hide();
  }

  void GUI::setCursorArrow(std::string const &p_arrow)
  {
    CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .getMouseCursor()
        .setDefaultImage(p_arrow);
  }

  CEGUI::Window *GUI::getRoot() const
  {
    return m_root;
  }

  void GUI::loadLayout(std::string const &p_path)
  {
    if (m_root)
      destroy();

    m_root = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(p_path);
    m_context->setRootWindow(m_root);
  }

  void GUI::addLayout(const std::string &layout)
  {
    nope::log::Log(Debug) << "Adding layout '" << layout << "'";
    CEGUI::Window *win =
        CEGUI::WindowManager::getSingleton().loadLayoutFromFile(layout);
    if (!win)
      throw(std::runtime_error("HUD layout not added"));
    m_root->addChild(win);
    m_windows[layout] = win;
    nope::log::Log(Debug) << "Layout '" << layout << "' added";
  }

  void GUI::removeLayout(const std::string &layout)
  {
    if (m_windows.find(layout) == m_windows.end())
      throw(std::runtime_error("Tried to remove unadded layout"));
    nope::log::Log(Debug) << "Removing layout '" << layout << "'";
    m_root->removeChild(m_windows[layout]);
    m_windows[layout] = nullptr;
    nope::log::Log(Debug) << "Layout '" << layout << "' removed";
  }
}
