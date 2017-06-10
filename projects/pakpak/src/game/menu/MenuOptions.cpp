//
// Created by brout_m on 09/06/17.
//

#include "game/menu/MenuOptions.hpp"

core::MenuOptions::MenuOptions(menu::MenuManager &menuManager, GUI &gui) :
  m_gui(gui), m_curState(core::GameState::Menu), m_menuManager(menuManager)

{
}

void core::MenuOptions::draw()
{
}

void core::MenuOptions::entry()
{
  m_gui.loadLayout("options.layout");
  m_gui.setCursorArrow("TaharezLook/MouseArrow");

  m_gui.getRoot()
      ->getChild("back_button")
      ->subscribeEvent(CEGUI::PushButton::EventClicked,
                       CEGUI::Event::Subscriber(&MenuOptions::onBackClick, this));
  m_gui.getRoot()
      ->getChild("edit_button")
      ->subscribeEvent(CEGUI::PushButton::EventClicked,
                       CEGUI::Event::Subscriber(&MenuOptions::onKeymapEdit, this));
}

void core::MenuOptions::exit()
{
}

void core::MenuOptions::destroy()
{
}

core::GameState core::MenuOptions::update() const
{
  return m_curState;
}

void core::MenuOptions::build()
{
}

bool core::MenuOptions::keyPressed(const OIS::KeyEvent &arg)
{
  CEGUI::GUIContext &context =
      CEGUI::System::getSingleton().getDefaultGUIContext();
  context.injectKeyDown((CEGUI::Key::Scan)arg.key);
  context.injectChar((CEGUI::Key::Scan)arg.text);
  return true;
}

bool core::MenuOptions::mouseMoved(const OIS::MouseEvent &arg)
{
  return CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
      static_cast<float>(arg.state.X.rel),
      static_cast<float>(arg.state.Y.rel));
}

bool core::MenuOptions::mousePressed(const OIS::MouseEvent &arg,
                                     OIS::MouseButtonID     id)
{
  (void)arg;
  return CEGUI::System::getSingleton()
      .getDefaultGUIContext()
      .injectMouseButtonDown(convertButton(id));
}

bool core::MenuOptions::mouseReleased(const OIS::MouseEvent &arg,
                                      OIS::MouseButtonID     id)
{
  (void)arg;
  return CEGUI::System::getSingleton()
      .getDefaultGUIContext()
      .injectMouseButtonUp(convertButton(id));
}

bool core::MenuOptions::keyReleased(const OIS::KeyEvent &arg)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
      (CEGUI::Key::Scan)arg.key);
  return true;
}

CEGUI::MouseButton core::MenuOptions::convertButton(OIS::MouseButtonID buttonID)
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

bool core::MenuOptions::onBackClick(CEGUI::EventArgs const &) {
  m_menuManager.popLayer();
  m_menuManager.begin();
  return false;
}

bool core::MenuOptions::onKeymapEdit(CEGUI::EventArgs const &)
{
  m_menuManager.push(core::MenuState::Keymap);
  m_menuManager.begin();
  return true;
}
