//
// Created by brout_m on 12/06/17.
//

#include "game/menu/InGameHUD.hpp"

core::InGameHUD::InGameHUD(menu::MenuManager &menuManager, GUI &gui) :
    m_gui(gui), m_curState(core::GameState::Menu), m_menuManager(menuManager)

{
}

void core::InGameHUD::draw()
{
}

void core::InGameHUD::entry()
{
  m_gui.loadLayout("gui_ingame.layout");
  m_gui.setCursorArrow("TaharezLook/MouseArrow");
}

void core::InGameHUD::exit()
{
}

void core::InGameHUD::destroy()
{
}

core::GameState core::InGameHUD::update() const
{
  return m_curState;
}

void core::InGameHUD::build()
{
}

bool core::InGameHUD::keyPressed(const OIS::KeyEvent &arg)
{
  CEGUI::GUIContext &context =
      CEGUI::System::getSingleton().getDefaultGUIContext();
  context.injectKeyDown((CEGUI::Key::Scan)arg.key);
  context.injectChar((CEGUI::Key::Scan)arg.text);
  return true;
}

bool core::InGameHUD::mouseMoved(const OIS::MouseEvent &arg)
{
  return CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
      static_cast<float>(arg.state.X.rel),
      static_cast<float>(arg.state.Y.rel));
}

bool core::InGameHUD::mousePressed(const OIS::MouseEvent &arg,
                                    OIS::MouseButtonID     id)
{
  (void)arg;
  return CEGUI::System::getSingleton()
      .getDefaultGUIContext()
      .injectMouseButtonDown(convertButton(id));
}

bool core::InGameHUD::mouseReleased(const OIS::MouseEvent &arg,
                                     OIS::MouseButtonID     id)
{
  (void)arg;
  return CEGUI::System::getSingleton()
      .getDefaultGUIContext()
      .injectMouseButtonUp(convertButton(id));
}

bool core::InGameHUD::keyReleased(const OIS::KeyEvent &arg)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
      (CEGUI::Key::Scan)arg.key);
  return true;
}

CEGUI::MouseButton core::InGameHUD::convertButton(OIS::MouseButtonID buttonID)
{
  switch (buttonID)
  {
    case OIS::MB_Left:
      return CEGUI::LeftButton;

    case OIS::MB_Right:
      return CEGUI::RightButton;

    case OIS::MB_Middle:
      return CEGUI::MiddleButton;

    default:
      return CEGUI::LeftButton;
  }
}
