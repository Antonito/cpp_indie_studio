//
// Created by brout_m on 12/06/17.
//

#include "game/menu/InGamePause.hpp"

core::InGamePause::InGamePause(menu::MenuManager &menuManager, GUI &gui) :
    m_gui(gui), m_curState(core::GameState::Menu), m_menuManager(menuManager)

{
}

void core::InGamePause::draw()
{
}

void core::InGamePause::entry()
{
  m_gui.loadLayout("pause.layout");
  m_gui.setCursorArrow("TaharezLook/MouseArrow");
}

void core::InGamePause::exit()
{
}

void core::InGamePause::destroy()
{
}

core::GameState core::InGamePause::update() const
{
  return m_curState;
}

void core::InGamePause::build()
{
}

bool core::InGamePause::keyPressed(const OIS::KeyEvent &arg)
{
  CEGUI::GUIContext &context =
      CEGUI::System::getSingleton().getDefaultGUIContext();
  context.injectKeyDown((CEGUI::Key::Scan)arg.key);
  context.injectChar((CEGUI::Key::Scan)arg.text);
  return true;
}

bool core::InGamePause::mouseMoved(const OIS::MouseEvent &arg)
{
  return CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
      static_cast<float>(arg.state.X.rel),
      static_cast<float>(arg.state.Y.rel));
}

bool core::InGamePause::mousePressed(const OIS::MouseEvent &arg,
                                   OIS::MouseButtonID     id)
{
  (void)arg;
  return CEGUI::System::getSingleton()
      .getDefaultGUIContext()
      .injectMouseButtonDown(convertButton(id));
}

bool core::InGamePause::mouseReleased(const OIS::MouseEvent &arg,
                                    OIS::MouseButtonID     id)
{
  (void)arg;
  return CEGUI::System::getSingleton()
      .getDefaultGUIContext()
      .injectMouseButtonUp(convertButton(id));
}

bool core::InGamePause::keyReleased(const OIS::KeyEvent &arg)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
      (CEGUI::Key::Scan)arg.key);
  return true;
}

CEGUI::MouseButton core::InGamePause::convertButton(OIS::MouseButtonID buttonID)
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

bool core::InGamePause::onBackClick(CEGUI::EventArgs const &) {
  m_menuManager.popLayer();
  m_menuManager.begin();
  return false;
}