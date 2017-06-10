//
// Created by brout_m on 09/06/17.
//

#include "game/menu/MenuSolo.hpp"
#include "game/menu/AssetSetter.hpp"

core::MenuSolo::MenuSolo(menu::MenuManager &menuManager, GUI &gui)
    : m_gui(gui), m_curState(core::GameState::Menu), m_menuManager(menuManager)

{
}

void core::MenuSolo::draw()
{
}

void core::MenuSolo::entry()
{
  m_gui.loadLayout("soloplayer.layout");
  m_gui.setCursorArrow("TaharezLook/MouseArrow");

  m_gui.getRoot()
      ->getChild("back_button")
      ->subscribeEvent(CEGUI::PushButton::EventClicked,
                       CEGUI::Event::Subscriber(&MenuSolo::onBackClick, this));

  m_gui.getRoot()
      ->getChild("play_button")
      ->subscribeEvent(CEGUI::PushButton::EventClicked,
                       CEGUI::Event::Subscriber(&MenuSolo::onPlayClick, this));

  m_gui.getRoot()
      ->getChild("easy_button")
      ->subscribeEvent(CEGUI::PushButton::EventClicked,
                       CEGUI::Event::Subscriber(&MenuSolo::onEasyClick, this));

  m_gui.getRoot()
      ->getChild("hard_button")
      ->subscribeEvent(CEGUI::PushButton::EventClicked,
                       CEGUI::Event::Subscriber(&MenuSolo::onHardClick, this));
}

void core::MenuSolo::exit()
{
}

void core::MenuSolo::destroy()
{
}

core::GameState core::MenuSolo::update() const
{
  return m_curState;
}

void core::MenuSolo::build()
{
}

bool core::MenuSolo::keyPressed(const OIS::KeyEvent &arg)
{
  CEGUI::GUIContext &context =
      CEGUI::System::getSingleton().getDefaultGUIContext();
  context.injectKeyDown((CEGUI::Key::Scan)arg.key);
  context.injectChar((CEGUI::Key::Scan)arg.text);
  return true;
}

bool core::MenuSolo::mouseMoved(const OIS::MouseEvent &arg)
{
  return CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
      static_cast<float>(arg.state.X.rel),
      static_cast<float>(arg.state.Y.rel));
}

bool core::MenuSolo::mousePressed(const OIS::MouseEvent &arg,
                                  OIS::MouseButtonID     id)
{
  (void)arg;
  return CEGUI::System::getSingleton()
      .getDefaultGUIContext()
      .injectMouseButtonDown(convertButton(id));
}

bool core::MenuSolo::mouseReleased(const OIS::MouseEvent &arg,
                                   OIS::MouseButtonID     id)
{
  (void)arg;
  return CEGUI::System::getSingleton()
      .getDefaultGUIContext()
      .injectMouseButtonUp(convertButton(id));
}

bool core::MenuSolo::keyReleased(const OIS::KeyEvent &arg)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
      (CEGUI::Key::Scan)arg.key);
  return true;
}

CEGUI::MouseButton core::MenuSolo::convertButton(OIS::MouseButtonID buttonID)
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

bool core::MenuSolo::onBackClick(CEGUI::EventArgs const &)
{
  m_menuManager.popLayer();
  m_menuManager.begin();
  return false;
}

bool core::MenuSolo::onPlayClick(CEGUI::EventArgs const &e)
{
  (void)e;
  m_curState = core::GameState::InGame;
  m_gui.hideCursor();
  return true;
}

bool core::MenuSolo::onEasyClick(CEGUI::EventArgs const &)
{
  CEGUI::Window &easyButton = *m_gui.getRoot()->getChild("easy_button");
  CEGUI::Window &hardButton = *m_gui.getRoot()->getChild("hard_button");

  core::AssetSetter::setButtonBack(easyButton, core::AssetSetter::BUTTON_COLOR::BYELLOW);
  core::AssetSetter::setTextColor(easyButton, core::AssetSetter::TEXT_COLOR::TRED);

  core::AssetSetter::setButtonBack(hardButton, core::AssetSetter::BUTTON_COLOR::BGREY);
  core::AssetSetter::setTextColor(hardButton, core::AssetSetter::TEXT_COLOR::TBLACK);
  return true;
}

bool core::MenuSolo::onHardClick(CEGUI::EventArgs const &)
{
  CEGUI::Window &easyButton = *m_gui.getRoot()->getChild("easy_button");
  CEGUI::Window &hardButton = *m_gui.getRoot()->getChild("hard_button");

  core::AssetSetter::setButtonBack(hardButton, core::AssetSetter::BUTTON_COLOR::BYELLOW);
  core::AssetSetter::setTextColor(hardButton, core::AssetSetter::TEXT_COLOR::TRED);

  core::AssetSetter::setButtonBack(easyButton, core::AssetSetter::BUTTON_COLOR::BGREY);
  core::AssetSetter::setTextColor(easyButton, core::AssetSetter::TEXT_COLOR::TBLACK);
  return true;
}
