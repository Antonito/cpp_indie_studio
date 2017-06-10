//
// Created by duhieu_b on 23/05/17.
//

#include <iostream>
#include "game/menu/GUI.hpp"

void core::GUI::init()
{
  m_renderer = &CEGUI::OgreRenderer::bootstrapSystem();
  CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
  CEGUI::Font::setDefaultResourceGroup("Fonts");
  CEGUI::Scheme::setDefaultResourceGroup("Schemes");
  CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
  CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
  m_context = &CEGUI::System::getSingleton().getDefaultGUIContext();
  loadSheme("TaharezLook.scheme");
}

void core::GUI::destroy()
{
  CEGUI::WindowManager::getSingleton().destroyWindow(m_root);
  m_root = nullptr;
}

void core::GUI::setFont(std::string const &p_font)
{
  CEGUI::FontManager::getSingleton().createFromFile(p_font + ".font");
  m_context->setDefaultFont(p_font);
}

CEGUI::Window *core::GUI::createButton(CEGUI::Window *    p_win,
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

CEGUI::Window *core::GUI::createButton(std::string const &p_type,
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

void core::GUI::setPos(CEGUI::Window *p_win, glm::vec4 const &p_dim1,
                       glm::vec4 const &p_dim2)
{
  p_win->setPosition(CEGUI::UVector2(CEGUI::UDim(p_dim1.x, p_dim2.x),
                                     CEGUI::UDim(p_dim1.y, p_dim2.y)));
  p_win->setSize(CEGUI::USize(CEGUI::UDim(p_dim1.z, p_dim2.z),
                              CEGUI::UDim(p_dim1.w, p_dim2.w)));
}

CEGUI::OgreRenderer *core::GUI::getRender() const
{
  return m_renderer;
}

CEGUI::GUIContext *core::GUI::getContext() const
{
  return m_context;
}

core::GUI::~GUI()
{
}

void core::GUI::draw()
{
}

core::GUI::GUI() : m_renderer(nullptr),
                   m_root(nullptr),
                   m_context(nullptr),
                   m_param()
{
  #if defined(_WIN32)
  m_param.insert(std::make_pair(std::string("w32_mouse"),
                                std::string("DISCL_FOREGROUND")));
  m_param.insert(std::make_pair(std::string("w32_mouse"),
                                std::string("DISCL_NONEXCLUSIVE")));
  m_param.insert(std::make_pair(std::string("w32_keyboard"),
                                std::string("DISCL_FOREGROUND")));
  m_param.insert(std::make_pair(std::string("w32_keyboard"),
                                std::string("DISCL_NONEXCLUSIVE")));
  #else
  m_param.insert(
      std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
  m_param.insert(
      std::make_pair(std::string("x11_mouse_hide"), std::string("true")));
  m_param.insert(
      std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
  m_param.insert(
      std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
  #endif

  init();
}

void core::GUI::loadSheme(std::string const &p_shem)
{
  CEGUI::SchemeManager::getSingleton().createFromFile(p_shem);
}

void core::GUI::hideCursor()
{
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();
}

void core::GUI::setCursorArrow(std::string const &p_arrow)
{
  CEGUI::System::getSingleton()
      .getDefaultGUIContext()
      .getMouseCursor()
      .setDefaultImage(p_arrow);
}

CEGUI::Window *core::GUI::getRoot() const
{
  return m_root;
}

void core::GUI::loadLayout(std::string const &p_path)
{
  if (m_root)
    destroy();
  m_root = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(p_path);
  m_context->setRootWindow(m_root);
}
