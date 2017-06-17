//
// Created by brout_m on 09/06/17.
//

#include "pakpak_stdafx.hpp"

namespace core
{
  MenuOptions::MenuOptions(menu::MenuManager &menuManager, GUI &gui)
      : m_gui(gui), m_curState(GameState::Menu), m_menuManager(menuManager),
        m_volumeButtons(), m_volumeSelected(4), m_graphicButtons(),
        m_graphicSelected(0)
  {
  }

  void MenuOptions::draw()
  {
  }

  void MenuOptions::entry()
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

  void MenuOptions::exit()
  {
  }

  void MenuOptions::destroy()
  {
  }

  GameState MenuOptions::update() const
  {
    return m_curState;
  }

  void MenuOptions::build()
  {
  }

  bool MenuOptions::keyPressed(const OIS::KeyEvent &arg)
  {
    CEGUI::GUIContext &context =
        CEGUI::System::getSingleton().getDefaultGUIContext();
    context.injectKeyDown(static_cast<CEGUI::Key::Scan>(arg.key));
    context.injectChar(static_cast<CEGUI::Key::Scan>(arg.text));
    return true;
  }

  bool MenuOptions::mouseMoved(const OIS::MouseEvent &arg)
  {
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseMove(static_cast<float>(arg.state.X.rel),
                         static_cast<float>(arg.state.Y.rel));
  }

  bool MenuOptions::mousePressed(const OIS::MouseEvent &arg,
                                 OIS::MouseButtonID     id)
  {
    (void)arg;
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseButtonDown(convertButton(id));
  }

  bool MenuOptions::mouseReleased(const OIS::MouseEvent &arg,
                                  OIS::MouseButtonID     id)
  {
    (void)arg;
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseButtonUp(convertButton(id));
  }

  bool MenuOptions::keyReleased(const OIS::KeyEvent &arg)
  {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
        static_cast<CEGUI::Key::Scan>(arg.key));
    return true;
  }

  CEGUI::MouseButton MenuOptions::convertButton(OIS::MouseButtonID buttonID)
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

  bool MenuOptions::onBackClick(CEGUI::EventArgs const &)
  {
    m_menuManager.popLayer();
    m_menuManager.begin();
    return false;
  }

  bool MenuOptions::onKeymapEdit(CEGUI::EventArgs const &)
  {
    m_menuManager.push(MenuState::Keymap);
    m_menuManager.begin();
    return true;
  }

  void MenuOptions::swapButtons(CEGUI::Window **tab, size_t &old,
                                size_t                          newSelected,
                                AssetSetter::ButtonStyle const &unselected,
                                AssetSetter::ButtonStyle const &selected)
  {
    if (newSelected != old)
      {
	AssetSetter::setTextColor(*tab[old], unselected.text);
	AssetSetter::setButtonBack(*tab[old], unselected.button);
	old = newSelected;
	AssetSetter::setTextColor(*tab[old], selected.text);
	AssetSetter::setButtonBack(*tab[old], selected.button);
      }
  }

  bool MenuOptions::onVolumeLevel0(CEGUI::EventArgs const &)
  {
    swapButtons(m_volumeButtons, m_volumeSelected, 0, AssetSetter::greyButton,
                AssetSetter::redButton);
    return true;
  }

  bool MenuOptions::onVolumeLevel25(CEGUI::EventArgs const &)
  {
    swapButtons(m_volumeButtons, m_volumeSelected, 1, AssetSetter::greyButton,
                AssetSetter::redButton);
    return true;
  }

  bool MenuOptions::onVolumeLevel50(CEGUI::EventArgs const &)
  {
    swapButtons(m_volumeButtons, m_volumeSelected, 2, AssetSetter::greyButton,
                AssetSetter::redButton);
    return true;
  }

  bool MenuOptions::onVolumeLevel75(CEGUI::EventArgs const &)
  {
    swapButtons(m_volumeButtons, m_volumeSelected, 3, AssetSetter::greyButton,
                AssetSetter::redButton);
    return true;
  }

  bool MenuOptions::onVolumeLevel100(CEGUI::EventArgs const &)
  {
    swapButtons(m_volumeButtons, m_volumeSelected, 4, AssetSetter::greyButton,
                AssetSetter::redButton);
    return true;
  }

  bool MenuOptions::onLowClick(CEGUI::EventArgs const &)
  {
    swapButtons(m_graphicButtons, m_graphicSelected, 0,
                AssetSetter::greyButton, AssetSetter::yellowButton);
    return true;
  }

  bool MenuOptions::onHighClick(CEGUI::EventArgs const &)
  {
    swapButtons(m_graphicButtons, m_graphicSelected, 1,
                AssetSetter::greyButton, AssetSetter::yellowButton);
    return true;
  }
}
