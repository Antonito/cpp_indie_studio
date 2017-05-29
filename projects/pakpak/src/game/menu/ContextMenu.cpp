#include "pakpak_stdafx.hpp"
#include "ContextMenu.hpp"

namespace menu
{
  ContextMenu::ContextMenu(Ogre::RenderWindow *win, core::InputListener *input)
      : core::AContext(win, input), m_viewport(nullptr), m_camera(nullptr), m_menuLayer({}), m_gui({})
  {
    m_menuLayer[static_cast<size_t>(core::MenuState::MainMenu)] =
            std::make_unique<core::MainMenu>();
    /*m_menuLayer[static_cast<size_t>(core::MenuState::Option)] =
            std::make_unique<core::Option>();
    m_menuLayer[static_cast<size_t>(core::MenuState::Score] =
            std::make_unique<core::Score>();
    m_menuLayer[static_cast<size_t>(core::MenuState::SoloPlayerGame)] =
            std::make_unique<core::SoloPlayerGame>();
    m_menuLayer[static_cast<size_t>(core::MenuState::MultiPlayerGame)] =
            std::make_unique<core::MultiPlayerGame>();*/
    m_gui.push(m_menuLayer[static_cast<size_t>(core::MenuState::MainMenu)].get());
    m_gui.top()->entry();
  }

  ContextMenu::~ContextMenu()
  {
    m_gui.top()->destroy();
  }

  void ContextMenu::enable()
  {
    // m_win->addViewport();
  }

  void ContextMenu::disable()
  {
  }

  core::GameState ContextMenu::update()
  {
    return m_gui.top()->update();
  }

  void ContextMenu::display()
  {
    m_gui.top()->draw();
  }
}
