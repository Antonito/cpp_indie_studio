//
// Created by brout_m on 09/06/17.
//

#include "game/menu/AssetSetter.hpp"
#include "game/menu/MenuKeymap.hpp"

core::MenuKeymap::MenuKeymap(menu::MenuManager &menuManager, GUI &gui)
    : m_gui(gui), m_curState(core::GameState::Menu),
      m_menuManager(menuManager), m_playerSelected(0), m_buttons()

{
}

void core::MenuKeymap::draw()
{
}

void core::MenuKeymap::entry()
{
  m_gui.loadLayout("keymap.layout");
  m_gui.setCursorArrow("TaharezLook/MouseArrow");

  m_buttons[0] = m_gui.getRoot()->getChild("player1_button");
  m_buttons[1] = m_gui.getRoot()->getChild("player2_button");
  m_buttons[2] = m_gui.getRoot()->getChild("player3_button");
  m_buttons[3] = m_gui.getRoot()->getChild("player4_button");

  m_gui.getRoot()
      ->getChild("back_button")
      ->subscribeEvent(
          CEGUI::PushButton::EventClicked,
          CEGUI::Event::Subscriber(&MenuKeymap::onBackClick, this));

  m_buttons[0]->subscribeEvent(
      CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&MenuKeymap::onPlayer1Click, this));
  m_buttons[1]->subscribeEvent(
      CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&MenuKeymap::onPlayer2Click, this));
  m_buttons[2]->subscribeEvent(
      CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&MenuKeymap::onPlayer3Click, this));
  m_buttons[3]->subscribeEvent(
      CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&MenuKeymap::onPlayer4Click, this));
}

void core::MenuKeymap::exit()
{
}

void core::MenuKeymap::destroy()
{
}

core::GameState core::MenuKeymap::update() const
{
  return m_curState;
}

void core::MenuKeymap::build()
{
}

bool core::MenuKeymap::keyPressed(const OIS::KeyEvent &arg)
{
  CEGUI::GUIContext &context =
      CEGUI::System::getSingleton().getDefaultGUIContext();
  context.injectKeyDown((CEGUI::Key::Scan)arg.key);
  context.injectChar((CEGUI::Key::Scan)arg.text);
  return true;
}

bool core::MenuKeymap::mouseMoved(const OIS::MouseEvent &arg)
{
  return CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
      static_cast<float>(arg.state.X.rel),
      static_cast<float>(arg.state.Y.rel));
}

bool core::MenuKeymap::mousePressed(const OIS::MouseEvent &arg,
                                    OIS::MouseButtonID     id)
{
  (void)arg;
  return CEGUI::System::getSingleton()
      .getDefaultGUIContext()
      .injectMouseButtonDown(convertButton(id));
}

bool core::MenuKeymap::mouseReleased(const OIS::MouseEvent &arg,
                                     OIS::MouseButtonID     id)
{
  (void)arg;
  return CEGUI::System::getSingleton()
      .getDefaultGUIContext()
      .injectMouseButtonUp(convertButton(id));
}

bool core::MenuKeymap::keyReleased(const OIS::KeyEvent &arg)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
      (CEGUI::Key::Scan)arg.key);
  return true;
}

CEGUI::MouseButton core::MenuKeymap::convertButton(OIS::MouseButtonID buttonID)
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

bool core::MenuKeymap::onBackClick(CEGUI::EventArgs const &)
{
  m_menuManager.popLayer();
  m_menuManager.begin();
  return true;
}

void core::MenuKeymap::swapButtons(size_t newSelected)
{
  if (newSelected != m_playerSelected)
    {
      core::AssetSetter::setTextColor(*m_buttons[m_playerSelected],
                                      core::AssetSetter::TEXT_COLOR::TBLACK);
      core::AssetSetter::setButtonBack(*m_buttons[m_playerSelected],
                                       core::AssetSetter::BUTTON_COLOR::BGREY);

      m_playerSelected = newSelected;
      core::AssetSetter::setTextColor(*m_buttons[m_playerSelected],
                                      core::AssetSetter::TEXT_COLOR::TBLUE);
      core::AssetSetter::setButtonBack(
          *m_buttons[m_playerSelected],
          core::AssetSetter::BUTTON_COLOR::BGREEN);
    }
}

bool core::MenuKeymap::onPlayer1Click(CEGUI::EventArgs const &)
{
  swapButtons(0);
  return true;
}

bool core::MenuKeymap::onPlayer2Click(CEGUI::EventArgs const &)
{
  swapButtons(1);
  return true;
}

bool core::MenuKeymap::onPlayer3Click(CEGUI::EventArgs const &)
{
  swapButtons(2);
  return true;
}

bool core::MenuKeymap::onPlayer4Click(CEGUI::EventArgs const &)
{
  swapButtons(3);
  return true;
}