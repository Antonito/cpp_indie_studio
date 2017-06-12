//
// Created by brout_m on 09/06/17.
//

#include "game/menu/AssetSetter.hpp"
#include "game/menu/MenuOptions.hpp"

core::MenuOptions::MenuOptions(menu::MenuManager &menuManager, GUI &gui)
    : m_gui(gui), m_curState(core::GameState::Menu),
      m_menuManager(menuManager), m_volumeButtons(), m_volumeSelected(4),
      m_graphicButtons(), m_graphicSelected(0)
{
}

void core::MenuOptions::draw()
{
}

void core::MenuOptions::entry()
{
  m_gui.loadLayout("options.layout");
  m_gui.setCursorArrow("TaharezLook/MouseArrow");

  m_graphicSelected = 0;
  m_volumeSelected = 4;
  m_volumeButtons[0] = m_gui.getRoot()->getChild("volume/level_0");
  m_volumeButtons[1] = m_gui.getRoot()->getChild("volume/level_25");
  m_volumeButtons[2] = m_gui.getRoot()->getChild("volume/level_50");
  m_volumeButtons[3] = m_gui.getRoot()->getChild("volume/level_75");
  m_volumeButtons[4] = m_gui.getRoot()->getChild("volume/level_100");
  m_graphicButtons[0] = m_gui.getRoot()->getChild("low_button");
  m_graphicButtons[1] = m_gui.getRoot()->getChild("high_button");

  m_gui.getRoot()
      ->getChild("back_button")
      ->subscribeEvent(
          CEGUI::PushButton::EventClicked,
          CEGUI::Event::Subscriber(&MenuOptions::onBackClick, this));
  m_gui.getRoot()
      ->getChild("edit_button")
      ->subscribeEvent(
          CEGUI::PushButton::EventClicked,
          CEGUI::Event::Subscriber(&MenuOptions::onKeymapEdit, this));

  m_volumeButtons[0]->subscribeEvent(
      CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&MenuOptions::onVolumeLevel0, this));
  m_volumeButtons[1]->subscribeEvent(
      CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&MenuOptions::onVolumeLevel25, this));
  m_volumeButtons[2]->subscribeEvent(
      CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&MenuOptions::onVolumeLevel50, this));
  m_volumeButtons[3]->subscribeEvent(
      CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&MenuOptions::onVolumeLevel75, this));
  m_volumeButtons[4]->subscribeEvent(
      CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&MenuOptions::onVolumeLevel100, this));
  m_graphicButtons[0]->subscribeEvent(
      CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&MenuOptions::onLowClick, this));
  m_graphicButtons[1]->subscribeEvent(
      CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&MenuOptions::onHighClick, this));
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

CEGUI::MouseButton
    core::MenuOptions::convertButton(OIS::MouseButtonID buttonID)
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

bool core::MenuOptions::onBackClick(CEGUI::EventArgs const &)
{
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

void core::MenuOptions::swapButtons(
    CEGUI::Window **tab, size_t &old, size_t newSelected,
    core::AssetSetter::ButtonStyle const &unselected,
    core::AssetSetter::ButtonStyle const &selected)
{
  if (newSelected != old)
    {
      core::AssetSetter::setTextColor(*tab[old], unselected.text);
      core::AssetSetter::setButtonBack(*tab[old], unselected.button);
      old = newSelected;
      core::AssetSetter::setTextColor(*tab[old], selected.text);
      core::AssetSetter::setButtonBack(*tab[old], selected.button);
    }
}

bool core::MenuOptions::onVolumeLevel0(CEGUI::EventArgs const &)
{
  swapButtons(m_volumeButtons, m_volumeSelected, 0,
              core::AssetSetter::greyButton, core::AssetSetter::redButton);
  return true;
}

bool core::MenuOptions::onVolumeLevel25(CEGUI::EventArgs const &)
{
  swapButtons(m_volumeButtons, m_volumeSelected, 1,
              core::AssetSetter::greyButton, core::AssetSetter::redButton);
  return true;
}

bool core::MenuOptions::onVolumeLevel50(CEGUI::EventArgs const &)
{
  swapButtons(m_volumeButtons, m_volumeSelected, 2,
              core::AssetSetter::greyButton, core::AssetSetter::redButton);
  return true;
}

bool core::MenuOptions::onVolumeLevel75(CEGUI::EventArgs const &)
{
  swapButtons(m_volumeButtons, m_volumeSelected, 3,
              core::AssetSetter::greyButton, core::AssetSetter::redButton);
  return true;
}

bool core::MenuOptions::onVolumeLevel100(CEGUI::EventArgs const &)
{
  swapButtons(m_volumeButtons, m_volumeSelected, 4,
              core::AssetSetter::greyButton, core::AssetSetter::redButton);
  return true;
}

bool core::MenuOptions::onLowClick(CEGUI::EventArgs const &)
{
  swapButtons(m_graphicButtons, m_graphicSelected, 0,
              core::AssetSetter::greyButton, core::AssetSetter::yellowButton);
  return true;
}

bool core::MenuOptions::onHighClick(CEGUI::EventArgs const &)
{
  swapButtons(m_graphicButtons, m_graphicSelected, 1,
              core::AssetSetter::greyButton, core::AssetSetter::yellowButton);
  return true;
}
