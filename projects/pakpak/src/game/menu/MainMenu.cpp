#include "game/menu/MainMenu.hpp"

core::MainMenu::MainMenu(menu::MenuManager &menuManager, GUI &gui)
    : m_gui(gui), m_curState(core::GameState::Menu), m_menuManager(menuManager)
{
}

void core::MainMenu::entry()
{
  initGUI();
}

void core::MainMenu::initGUI()
{
  m_gui.loadLayout("indie.layout");

  m_gui.getRoot()
      ->getChild("quit_button")
      ->subscribeEvent(CEGUI::PushButton::EventClicked,
                       CEGUI::Event::Subscriber(&MainMenu::onExitClick, this));
  m_gui.getRoot()
      ->getChild("play_button")
      ->subscribeEvent(CEGUI::PushButton::EventClicked,
                       CEGUI::Event::Subscriber(&MainMenu::onSoloClick, this));
  m_gui.getRoot()
      ->getChild("options_button")
      ->subscribeEvent(
          CEGUI::PushButton::EventClicked,
          CEGUI::Event::Subscriber(&MainMenu::onOptionClick, this));

  m_gui.getRoot()
      ->getChild("multi")
      ->subscribeEvent(
          CEGUI::PushButton::EventClicked,
          CEGUI::Event::Subscriber(&MainMenu::onMultiClick, this));

  m_gui.getRoot()
      ->getChild("stats_button")
      ->subscribeEvent(
          CEGUI::PushButton::EventClicked,
          CEGUI::Event::Subscriber(&MainMenu::onScoreClick, this));

  m_gui.setCursorArrow("TaharezLook/MouseArrow");
}

bool core::MainMenu::keyPressed(OIS::KeyEvent const &arg)
{
  CEGUI::GUIContext &context =
      CEGUI::System::getSingleton().getDefaultGUIContext();
  context.injectKeyDown((CEGUI::Key::Scan)arg.key);
  context.injectChar((CEGUI::Key::Scan)arg.text);
  return true;
}

bool core::MainMenu::mouseMoved(OIS::MouseEvent const &arg)
{
  return CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
      static_cast<float>(arg.state.X.rel),
      static_cast<float>(arg.state.Y.rel));
}

bool core::MainMenu::mousePressed(OIS::MouseEvent const &arg,
                                  OIS::MouseButtonID     id)
{
  (void)arg;
  return CEGUI::System::getSingleton()
      .getDefaultGUIContext()
      .injectMouseButtonDown(convertButton(id));
}

bool core::MainMenu::mouseReleased(OIS::MouseEvent const &arg,
                                   OIS::MouseButtonID     id)
{
  (void)arg;
  return CEGUI::System::getSingleton()
      .getDefaultGUIContext()
      .injectMouseButtonUp(convertButton(id));
}

bool core::MainMenu::keyReleased(OIS::KeyEvent const &arg)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
      (CEGUI::Key::Scan)arg.key);
  return true;
}

CEGUI::MouseButton core::MainMenu::convertButton(OIS::MouseButtonID buttonID)
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

void core::MainMenu::destroy()
{
  m_gui.destroy();
}

core::GameState core::MainMenu::update() const
{
  return m_curState;
}

void core::MainMenu::draw()
{
}

void core::MainMenu::exit()
{
}

void core::MainMenu::build()
{
}

bool core::MainMenu::onOptionClick(CEGUI::EventArgs const &)
{
  m_menuManager.push(core::MenuState::Option);
  m_menuManager.begin();
  return true;
}

bool core::MainMenu::onExitClick(CEGUI::EventArgs const &)
{
  m_curState = core::GameState::Quit;
  return true;
}

bool core::MainMenu::onSoloClick(CEGUI::EventArgs const &)
{
  m_menuManager.push(core::MenuState::SoloPlayerGame);
  m_menuManager.begin();
  return true;
}

bool core::MainMenu::onMultiClick(CEGUI::EventArgs const &)
{
  m_menuManager.push(core::MenuState::MultiPlayerGame);
  m_menuManager.begin();
  return true;
}

bool core::MainMenu::onScoreClick(CEGUI::EventArgs const &)
{
  m_menuManager.push(core::MenuState::Score);
  m_menuManager.begin();
  return true;
}