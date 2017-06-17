//
// Created by brout_m on 09/06/17.
//

#include "pakpak_stdafx.hpp"

namespace core
{
  MenuMultiplayer::MenuMultiplayer(menu::MenuManager &menuManager, GUI &gui,
                                   SoundManager &sound)
      : m_gui(gui), m_curState(GameState::Menu), m_menuManager(menuManager),
        m_sound(sound)

  {
  }

  void MenuMultiplayer::draw()
  {
  }

  void MenuMultiplayer::entry()
  {
    m_gui.loadLayout("multiplayer.layout");
    m_gui.setCursorArrow("TaharezLook/MouseArrow");

    m_gui.getRoot()
        ->getChild("back_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuMultiplayer::onBackClick, this));

    m_gui.getRoot()
        ->getChild("launch_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuMultiplayer::onPlayClick, this));
  }

  void MenuMultiplayer::exit()
  {
  }

  void MenuMultiplayer::destroy()
  {
  }

  GameState MenuMultiplayer::update() const
  {
    return m_curState;
  }

  void MenuMultiplayer::build()
  {
  }

  bool MenuMultiplayer::keyPressed(const OIS::KeyEvent &arg)
  {
    CEGUI::GUIContext &context =
        CEGUI::System::getSingleton().getDefaultGUIContext();
    context.injectKeyDown((CEGUI::Key::Scan)arg.key);
    context.injectChar((CEGUI::Key::Scan)arg.text);
    return true;
  }

  bool MenuMultiplayer::mouseMoved(const OIS::MouseEvent &arg)
  {
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseMove(static_cast<float>(arg.state.X.rel),
                         static_cast<float>(arg.state.Y.rel));
  }

  bool MenuMultiplayer::mousePressed(const OIS::MouseEvent &arg,
                                     OIS::MouseButtonID     id)
  {
    (void)arg;
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseButtonDown(convertButton(id));
  }

  bool MenuMultiplayer::mouseReleased(const OIS::MouseEvent &arg,
                                      OIS::MouseButtonID     id)
  {
    (void)arg;
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseButtonUp(convertButton(id));
  }

  bool MenuMultiplayer::keyReleased(const OIS::KeyEvent &arg)
  {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
        (CEGUI::Key::Scan)arg.key);
    return true;
  }

  CEGUI::MouseButton
      MenuMultiplayer::convertButton(OIS::MouseButtonID buttonID)
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

  bool MenuMultiplayer::onBackClick(CEGUI::EventArgs const &)
  {
    m_menuManager.popLayer();
    m_menuManager.begin();
    return false;
  }

  bool MenuMultiplayer::onPlayClick(CEGUI::EventArgs const &)
  {
    m_curState = GameState::InGame;
    m_gui.hideCursor();
    return true;
  }
}