#include "MainMenu.hpp"

void core::MainMenu::draw()
{
  m_gui.draw();
}

void core::MainMenu::entry()
{
  m_camera->setPosition(Ogre::Vector3(0, 0, 0));
  m_camera->lookAt(Ogre::Vector3(0, 0, 0));
  m_camera->setNearClipDistance(2);

  initGUI();
}

void core::MainMenu::exit()
{
  m_gui.destroy();
}

void core::MainMenu::destroy()
{
}

core::GameState core::MainMenu::update() const
{
  return m_curState;
}

void core::MainMenu::build()
{
}

void core::MainMenu::initGUI()
{
  m_gui.init("");
  m_gui.loadSheme("TaharezLook.scheme");
  m_gui.setFont("DejaVuSans-10");

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
  m_gui.showCursor();
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
    : m_sceneMan(Ogre::Root::getSingleton().createSceneManager(
          "DefaultSceneManager", "Menu scene manager")),
      m_gui(), m_curState(core::GameState::Menu),
      m_camera(m_sceneMan->createCamera("MenuCamera"))
{
}
