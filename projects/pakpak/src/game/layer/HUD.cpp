//
// Created by brout_m on 14/06/17.
//

#include "HUD.hpp"

core::HUD::HUD()
    : m_renderer(nullptr), m_rootWindow(nullptr), m_context(nullptr), m_param()
{
}

core::HUD::~HUD()
{
}

void core::HUD::initHUD()
{
}

void core::HUD::destroyHUD()
{
}

void core::HUD::loadScheme(const std::string &)
{
}

void core::HUD::loadLayout(const std::string &path)
{
  if (m_rootWindow)
    destroyHUD();
  m_rootWindow = CEGUI::WindowManager::get
}

void core::HUD::addLayout(const std::string &)
{
}

void core::HUD::removeLayout(const std::string &)
{
}

CEGUI::Window &core::HUD::getChild(const std::string &)
{
  return <#initializer #>;
}

void core::HUD::grabMouse()
{
}
