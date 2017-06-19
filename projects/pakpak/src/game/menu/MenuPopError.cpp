//
// Created by duhieu_b on 18/06/17.
//

#include "pakpak_stdafx.hpp"

core::MenuPopError::MenuPopError(menu::MenuManager &menuManager,
                                 core::GUI &gui, core::SoundManager &sound)
    : m_gui(gui), m_curState(GameState::Menu), m_menuManager(menuManager),
      m_sound(sound)
{
}

void core::MenuPopError::draw()
{
}

void core::MenuPopError::entry()
{
  initGUI();
}

void core::MenuPopError::exit()
{
}

void core::MenuPopError::destroy()
{
  m_gui.destroy();
}

core::GameState core::MenuPopError::update() const
{
  return m_curState;
}

void core::MenuPopError::build()
{
}

bool core::MenuPopError::keyPressed(const OIS::KeyEvent &arg)
{
  CEGUI::GUIContext &context =
      CEGUI::System::getSingleton().getDefaultGUIContext();
  context.injectKeyDown(static_cast<CEGUI::Key::Scan>(arg.key));
  context.injectChar(static_cast<CEGUI::Key::Scan>(arg.text));
  return true;
}

bool core::MenuPopError::mouseMoved(const OIS::MouseEvent &arg)
{
  return CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
      static_cast<float>(arg.state.X.rel),
      static_cast<float>(arg.state.Y.rel));
}

bool core::MenuPopError::mousePressed(const OIS::MouseEvent &,
                                      OIS::MouseButtonID id)
{
  return CEGUI::System::getSingleton()
      .getDefaultGUIContext()
      .injectMouseButtonDown(convertButton(id));
}

bool core::MenuPopError::mouseReleased(const OIS::MouseEvent &,
                                       OIS::MouseButtonID id)
{
  return CEGUI::System::getSingleton()
      .getDefaultGUIContext()
      .injectMouseButtonUp(convertButton(id));
}

bool core::MenuPopError::keyReleased(const OIS::KeyEvent &arg)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
      static_cast<CEGUI::Key::Scan>(arg.key));
  return true;
}

void core::MenuPopError::initGUI()
{
  m_gui.addLayout("server_error.layout");
  m_gui.setCursorArrow("TaharezLook/MouseArrow");

  if (m_gui.getRoot()->getChildRecursive("Button") == NULL)
    {
      throw std::exception();
      // TODO:Arthur find exception for button assets missing.
    }
  m_gui.getRoot()->getChildRecursive("Button")->subscribeEvent(
      CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&MenuPopError::onOkClick, this));
  m_gui.getRoot()->getChildRecursive("Button")->subscribeEvent(
      CEGUI::PushButton::EventMouseEntersArea,
      CEGUI::Event::Subscriber(&MenuPopError::onOkArea, this));
}

CEGUI::MouseButton
    core::MenuPopError::convertButton(OIS::MouseButtonID buttonID)
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

bool core::MenuPopError::onOkArea(CEGUI::EventArgs const &)
{
  soundPass();
  return true;
}

bool core::MenuPopError::onOkClick(CEGUI::EventArgs const &)
{
  soundClick();
  m_gui.removeLayout("server_error.layout");
  m_menuManager.popLayer();
  m_menuManager.begin();
  return true;
}

void core::MenuPopError::soundClick()
{
  m_sound.playSound(core::ESound::CLICK_BUTTON);
}

void core::MenuPopError::soundPass()
{
  m_sound.playSound(core::ESound::PASS_BUTTON);
}
