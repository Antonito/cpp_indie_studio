#include "MainMenu.hpp"

bool core::MainMenu::keyPressed(OIS::KeyEvent const& arg)
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

void core::MainMenu::entry()
{
  initGUI();
}

void core::MainMenu::destroy()
{
    m_gui.destroy();
    m_gui.hideCursor();
}

core::GameState core::MainMenu::update() const
{
  return m_curState;
}

void core::MainMenu::initGUI()
{
  m_gui.init("");
  m_gui.loadSheme("TaharezLook.scheme");
  m_gui.setFont("DejaVuSans-10");

#if defined(_WIN32)
  m_param.insert(std::make_pair(std::string("w32_mouse"),
                                std::string("DISCL_FOREGROUND")));
  m_param.insert(std::make_pair(std::string("w32_mouse"),
                                std::string("DISCL_NONEXCLUSIVE")));
  m_param.insert(std::make_pair(std::string("w32_keyboard"),
                                std::string("DISCL_FOREGROUND")));
  m_param.insert(std::make_pair(std::string("w32_keyboard"),
                                std::string("DISCL_NONEXCLUSIVE")));
#else
  m_param.insert(
      std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
  m_param.insert(
      std::make_pair(std::string("x11_mouse_hide"), std::string("true")));
  m_param.insert(
      std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
  m_param.insert(
      std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif
  CEGUI::PushButton *quitButton =
      static_cast<CEGUI::PushButton *>(m_gui.createButton(
          "TaharezLook/Button", glm::vec4(0.5f, 0.7f, 0.1f, 0.05f),
          glm::vec4(0.0), "ExitButton"));
  quitButton->setText("QUIT");
  quitButton->subscribeEvent(
      CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&MainMenu::onExitClick, this));

  CEGUI::PushButton *playButton =
      static_cast<CEGUI::PushButton *>(m_gui.createButton(
          "TaharezLook/Button", glm::vec4(0.5f, 0.5f, 0.1f, 0.05f),
          glm::vec4(0.0), "PlayButton"));
  playButton->setText("PLAY");
  playButton->subscribeEvent(
      CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&MainMenu::onPlayClick, this));
  m_gui.setCursorArrow("TaharezLook/MouseArrow");
}

bool core::MainMenu::onExitClick(CEGUI::EventArgs const &e)
{
  (void)e;
  std::cout << "Click on quit !!" << std::endl;
  m_curState = core::GameState::Quit;
  return true;
}

bool core::MainMenu::onPlayClick(CEGUI::EventArgs const &e)
{
  (void)e;
  std::cout << "Click on play !!" << std::endl;
  m_curState = core::GameState::InGame;
  return true;
}

core::MainMenu::MainMenu()
    : m_gui(), m_param(), m_curState(core::GameState::Menu)
{
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
