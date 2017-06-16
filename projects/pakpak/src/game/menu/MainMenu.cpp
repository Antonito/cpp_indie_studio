#include "pakpak_stdafx.hpp"

namespace core
{
  MainMenu::MainMenu(menu::MenuManager &menuManager, GUI &gui)
      : m_gui(gui), m_curState(GameState::Menu), m_menuManager(menuManager)
  {
  }

  void MainMenu::entry()
  {
    initGUI();
  }

  void MainMenu::initGUI()
  {
    m_gui.loadLayout("indie.layout");

    m_gui.getRoot()
        ->getChild("quit_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MainMenu::onExitClick, this));
    m_gui.getRoot()
        ->getChild("play_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MainMenu::onSoloClick, this));
    m_gui.getRoot()
        ->getChild("options_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MainMenu::onOptionClick, this));

    m_gui.getRoot()->getChild("multi")->subscribeEvent(
        CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(&MainMenu::onMultiClick, this));

    m_gui.getRoot()
        ->getChild("stats_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MainMenu::onScoreClick, this));

    m_gui.setCursorArrow("TaharezLook/MouseArrow");
  }

  bool MainMenu::keyPressed(OIS::KeyEvent const &arg)
  {
    CEGUI::GUIContext &context =
        CEGUI::System::getSingleton().getDefaultGUIContext();
    context.injectKeyDown(static_cast<CEGUI::Key::Scan>(arg.key));
    context.injectChar(static_cast<CEGUI::Key::Scan>(arg.text));
    return true;
  }

  bool MainMenu::mouseMoved(OIS::MouseEvent const &arg)
  {
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseMove(static_cast<float>(arg.state.X.rel),
                         static_cast<float>(arg.state.Y.rel));
  }

  bool MainMenu::mousePressed(OIS::MouseEvent const &arg,
                              OIS::MouseButtonID     id)
  {
    (void)arg;
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseButtonDown(convertButton(id));
  }

  bool MainMenu::mouseReleased(OIS::MouseEvent const &arg,
                               OIS::MouseButtonID     id)
  {
    (void)arg;
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseButtonUp(convertButton(id));
  }

  bool MainMenu::keyReleased(OIS::KeyEvent const &arg)
  {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
        static_cast<CEGUI::Key::Scan>(arg.key));
    return true;
  }

  CEGUI::MouseButton MainMenu::convertButton(OIS::MouseButtonID buttonID)
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

  void MainMenu::destroy()
  {
    m_gui.destroy();
  }

  GameState MainMenu::update() const
  {
    return m_curState;
  }

  void MainMenu::draw()
  {
  }

  void MainMenu::exit()
  {
  }

  void MainMenu::build()
  {
  }

  bool MainMenu::onOptionClick(CEGUI::EventArgs const &)
  {
    m_menuManager.push(MenuState::Option);
    m_menuManager.begin();
    return true;
  }

  bool MainMenu::onExitClick(CEGUI::EventArgs const &)
  {
    m_curState = GameState::Quit;
    return true;
  }

  bool MainMenu::onSoloClick(CEGUI::EventArgs const &)
  {
    m_menuManager.push(MenuState::SoloPlayerGame);
    m_menuManager.begin();
    return true;
  }

  bool MainMenu::onMultiClick(CEGUI::EventArgs const &)
  {
    m_menuManager.push(MenuState::MultiPlayerGame);
    m_menuManager.begin();
    return true;
  }

  bool MainMenu::onScoreClick(CEGUI::EventArgs const &)
  {
    m_menuManager.push(MenuState::Score);
    m_menuManager.begin();
    return true;
  }
}
