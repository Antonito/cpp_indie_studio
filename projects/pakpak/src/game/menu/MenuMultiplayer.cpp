//
// Created by brout_m on 09/06/17.
//

#include "game/menu/MenuMultiplayer.hpp"

core::MenuMultiplayer::MenuMultiplayer(menu::MenuManager &menuManager, GUI &gui) :
    m_gui(gui), m_curState(core::GameState::Menu), m_menuManager(menuManager)

{
}

void core::MenuMultiplayer::draw()
{
}

void core::MenuMultiplayer::entry()
{
  m_gui.loadLayout("multiplayer.layout");
  m_gui.setCursorArrow("TaharezLook/MouseArrow");

  m_gui.getRoot()
      ->getChild("back_button")
      ->subscribeEvent(CEGUI::PushButton::EventClicked,
                       CEGUI::Event::Subscriber(&MenuMultiplayer::onBackClick, this));

  m_gui.getRoot()
      ->getChild("launch_button")
      ->subscribeEvent(CEGUI::PushButton::EventClicked,
                       CEGUI::Event::Subscriber(&MenuMultiplayer::onPlayClick, this));
}

void core::MenuMultiplayer::exit()
{
}

void core::MenuMultiplayer::destroy()
{
}

core::GameState core::MenuMultiplayer::update() const
{
  return m_curState;
}

void core::MenuMultiplayer::build()
{
}

bool core::MenuMultiplayer::keyPressed(const OIS::KeyEvent &arg)
{
  CEGUI::GUIContext &context =
      CEGUI::System::getSingleton().getDefaultGUIContext();
  context.injectKeyDown((CEGUI::Key::Scan)arg.key);
  context.injectChar((CEGUI::Key::Scan)arg.text);
  return true;
}

bool core::MenuMultiplayer::mouseMoved(const OIS::MouseEvent &arg)
{
  return CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
      static_cast<float>(arg.state.X.rel),
      static_cast<float>(arg.state.Y.rel));
}

bool core::MenuMultiplayer::mousePressed(const OIS::MouseEvent &arg,
                                  OIS::MouseButtonID     id)
{
  (void)arg;
  return CEGUI::System::getSingleton()
      .getDefaultGUIContext()
      .injectMouseButtonDown(convertButton(id));
}

bool core::MenuMultiplayer::mouseReleased(const OIS::MouseEvent &arg,
                                   OIS::MouseButtonID     id)
{
  (void)arg;
  return CEGUI::System::getSingleton()
      .getDefaultGUIContext()
      .injectMouseButtonUp(convertButton(id));
}

bool core::MenuMultiplayer::keyReleased(const OIS::KeyEvent &arg)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
      (CEGUI::Key::Scan)arg.key);
  return true;
}

CEGUI::MouseButton core::MenuMultiplayer::convertButton(OIS::MouseButtonID buttonID)
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

bool core::MenuMultiplayer::onBackClick(CEGUI::EventArgs const &)
{
  m_menuManager.popLayer();
  m_menuManager.begin();
  return false;
}

bool core::MenuMultiplayer::onPlayClick(CEGUI::EventArgs const &)
{
  m_curState = core::GameState::InGame;
  m_gui.hideCursor();
  return true;
}