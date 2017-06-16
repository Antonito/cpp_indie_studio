//
// Created by brout_m on 14/06/17.
//

#include <CEGUI/CEGUI.h>
#include "HUD.hpp"
#include "Logger.hpp"

core::HUD::HUD()
    : m_renderer(nullptr), m_rootWindow(nullptr), m_context(nullptr),
      m_param(), m_windows({}), m_quit(false)
{
  initHUD();
}

core::HUD::~HUD()
{
}

void core::HUD::initHUD()
{
  nope::log::Log(Debug) << "Initiating HUD";
  m_context = &CEGUI::System::getSingleton().getDefaultGUIContext();
  loadScheme("TaharezLook.scheme");
}

void core::HUD::destroyHUD()
{
  nope::log::Log(Debug) << "Destroying HUD all windows";
  CEGUI::WindowManager::getSingleton().destroyAllWindows();
  m_rootWindow = nullptr;
}

void core::HUD::loadScheme(const std::string &scheme)
{
  CEGUI::SchemeManager::getSingleton().createFromFile(scheme);
}

void core::HUD::loadLayout(const std::string &layout)
{
  nope::log::Log(Debug) << "Loading layout '" << layout << "'";
  if (m_rootWindow)
    destroyHUD();
  m_rootWindow =
      CEGUI::WindowManager::getSingleton().loadLayoutFromFile(layout);
  if (!m_rootWindow)
    throw std::runtime_error("HUD layout not loaded");
  m_context->setRootWindow(m_rootWindow);
  nope::log::Log(Debug) << "Layout '" << layout << "' loaded";
}

void core::HUD::addLayout(const std::string &layout)
{
  nope::log::Log(Debug) << "Adding layout '" << layout << "'";
  CEGUI::Window *win =
      CEGUI::WindowManager::getSingleton().loadLayoutFromFile(layout);
  if (!win)
    throw(std::runtime_error("HUD layout not added"));
  m_rootWindow->addChild(win);
  m_windows[layout] = win;
  nope::log::Log(Debug) << "Layout '" << layout << "' added";
}

void core::HUD::removeLayout(const std::string &layout)
{
  if (m_windows.find(layout) == m_windows.end())
    throw (std::runtime_error("Tried to remove unadded layout"));
  nope::log::Log(Debug) << "Removing layout '" << layout << "'";
  m_rootWindow->removeChild(m_windows[layout]);
  m_windows[layout] = nullptr;
  nope::log::Log(Debug) << "Layout '" << layout << "' removed";
}

CEGUI::Window *core::HUD::getChild(const std::string &child)
{
  nope::log::Log(Debug) << "Getting child '" << child << "'";
  return m_rootWindow->getChild(child);
}

CEGUI::Window *core::HUD::getRoot()
{
  return m_rootWindow;
}

void core::HUD::grabMouse()
{
}

void core::HUD::showCursor(bool show)
{
  if (show)
    {
      nope::log::Log(Debug) << "Showing cursor";
      CEGUI::System::getSingleton()
          .getDefaultGUIContext()
          .getMouseCursor()
          .show();
    }
  else
    hideCursor(true);
}

void core::HUD::hideCursor(bool hide)
{
  if (hide)
    {
      nope::log::Log(Debug) << "Hiding cursor";
      CEGUI::System::getSingleton()
          .getDefaultGUIContext()
          .getMouseCursor()
          .hide();
    }
  else
    showCursor(true);
}

CEGUI::Window *core::HUD::operator[](CEGUI::Vector2f &vec)
{
  return m_rootWindow->getChildAtPosition(vec);
}

void core::HUD::setQuit(bool value)
{
  m_quit = value;
}

bool core::HUD::getQuit() const
{
  return m_quit;
}
