//
// Created by brout_m on 12/06/17.
//

#include "pakpak_stdafx.hpp"

namespace core
{
  MenuScores::MenuScores(menu::MenuManager &menuManager, GUI &gui)
      : m_gui(gui), m_curState(GameState::Menu), m_menuManager(menuManager)

  {
  }

  void MenuScores::draw()
  {
  }

  void MenuScores::entry()
  {
    m_gui.loadLayout("scores.layout");
    m_gui.setCursorArrow("TaharezLook/MouseArrow");

    m_gui.getRoot()
        ->getChild("back_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuScores::onBackClick, this));
  }

  void MenuScores::exit()
  {
  }

  void MenuScores::destroy()
  {
  }

  GameState MenuScores::update() const
  {
    return m_curState;
  }

  void MenuScores::build()
  {
  }

  bool MenuScores::keyPressed(const OIS::KeyEvent &arg)
  {
    CEGUI::GUIContext &context =
        CEGUI::System::getSingleton().getDefaultGUIContext();
    context.injectKeyDown((CEGUI::Key::Scan)arg.key);
    context.injectChar((CEGUI::Key::Scan)arg.text);
    return true;
  }

  bool MenuScores::mouseMoved(const OIS::MouseEvent &arg)
  {
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseMove(static_cast<float>(arg.state.X.rel),
                         static_cast<float>(arg.state.Y.rel));
  }

  bool MenuScores::mousePressed(const OIS::MouseEvent &arg,
                                OIS::MouseButtonID     id)
  {
    (void)arg;
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseButtonDown(convertButton(id));
  }

  bool MenuScores::mouseReleased(const OIS::MouseEvent &arg,
                                 OIS::MouseButtonID     id)
  {
    (void)arg;
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseButtonUp(convertButton(id));
  }

  bool MenuScores::keyReleased(const OIS::KeyEvent &arg)
  {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
        (CEGUI::Key::Scan)arg.key);
    return true;
  }

  CEGUI::MouseButton MenuScores::convertButton(OIS::MouseButtonID buttonID)
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

  bool MenuScores::onBackClick(CEGUI::EventArgs const &)
  {
    m_menuManager.popLayer();
    m_menuManager.begin();
    return false;
  }
}