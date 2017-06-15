//
// Created by brout_m on 09/06/17.
//

#include "pakpak_stdafx.hpp"

namespace core
{
  MenuSolo::MenuSolo(menu::MenuManager &menuManager, GUI &gui)
      : m_gui(gui), m_curState(GameState::Menu), m_menuManager(menuManager)

  {
  }

  void MenuSolo::draw()
  {
  }

  void MenuSolo::entry()
  {
    m_gui.loadLayout("soloplayer.layout");
    m_gui.setCursorArrow("TaharezLook/MouseArrow");
    m_curState = GameState::Menu;

    m_gui.getRoot()
        ->getChild("back_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuSolo::onBackClick, this));

    m_gui.getRoot()
        ->getChild("play_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuSolo::onPlayClick, this));

    m_gui.getRoot()
        ->getChild("easy_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuSolo::onEasyClick, this));

    m_gui.getRoot()
        ->getChild("hard_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuSolo::onHardClick, this));
  }

  void MenuSolo::exit()
  {
  }

  void MenuSolo::destroy()
  {
  }

  GameState MenuSolo::update() const
  {
    return m_curState;
  }

  void MenuSolo::build()
  {
  }

  bool MenuSolo::keyPressed(const OIS::KeyEvent &arg)
  {
    CEGUI::GUIContext &context =
        CEGUI::System::getSingleton().getDefaultGUIContext();
    context.injectKeyDown((CEGUI::Key::Scan)arg.key);
    context.injectChar((CEGUI::Key::Scan)arg.text);
    return true;
  }

  bool MenuSolo::mouseMoved(const OIS::MouseEvent &arg)
  {
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseMove(static_cast<float>(arg.state.X.rel),
                         static_cast<float>(arg.state.Y.rel));
  }

  bool MenuSolo::mousePressed(const OIS::MouseEvent &arg,
                              OIS::MouseButtonID     id)
  {
    (void)arg;
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseButtonDown(convertButton(id));
  }

  bool MenuSolo::mouseReleased(const OIS::MouseEvent &arg,
                               OIS::MouseButtonID     id)
  {
    (void)arg;
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseButtonUp(convertButton(id));
  }

  bool MenuSolo::keyReleased(const OIS::KeyEvent &arg)
  {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
        (CEGUI::Key::Scan)arg.key);
    return true;
  }

  CEGUI::MouseButton MenuSolo::convertButton(OIS::MouseButtonID buttonID)
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

  bool MenuSolo::onBackClick(CEGUI::EventArgs const &)
  {
    m_menuManager.popLayer();
    m_menuManager.begin();
    return false;
  }

  bool MenuSolo::onPlayClick(CEGUI::EventArgs const &e)
  {
    (void)e;
    m_curState = GameState::InGame;
    m_gui.hideCursor();
    return true;
  }

  bool MenuSolo::onEasyClick(CEGUI::EventArgs const &)
  {
    CEGUI::Window &easyButton = *m_gui.getRoot()->getChild("easy_button");
    CEGUI::Window &hardButton = *m_gui.getRoot()->getChild("hard_button");

    AssetSetter::setButtonBack(easyButton, AssetSetter::BUTTON_COLOR::BYELLOW);
    AssetSetter::setTextColor(easyButton, AssetSetter::TEXT_COLOR::TRED);

    AssetSetter::setButtonBack(hardButton, AssetSetter::BUTTON_COLOR::BGREY);
    AssetSetter::setTextColor(hardButton, AssetSetter::TEXT_COLOR::TBLACK);
    return true;
  }

  bool MenuSolo::onHardClick(CEGUI::EventArgs const &)
  {
    CEGUI::Window &easyButton = *m_gui.getRoot()->getChild("easy_button");
    CEGUI::Window &hardButton = *m_gui.getRoot()->getChild("hard_button");

    AssetSetter::setButtonBack(hardButton, AssetSetter::BUTTON_COLOR::BYELLOW);
    AssetSetter::setTextColor(hardButton, AssetSetter::TEXT_COLOR::TRED);

    AssetSetter::setButtonBack(easyButton, AssetSetter::BUTTON_COLOR::BGREY);
    AssetSetter::setTextColor(easyButton, AssetSetter::TEXT_COLOR::TBLACK);
    return true;
  }
}