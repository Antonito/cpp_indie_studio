#include "MainMenu.hpp"

void core::MainMenu::draw()
{
  m_gui.draw();
}

void core::MainMenu::entry()
{
  m_camera.setPosition(Ogre::Vector3(0, 0, 0));
  m_camera.lookAt(Ogre::Vector3(0, 0, 0));
  m_camera.setNearClipDistance(2);

  initGUI();
}

void core::MainMenu::exit()
{
  m_gui.destroy();
}

void core::MainMenu::destroy()
{
}

GameState core::MainMenu::update() const
{
  return m_curState;
}

void core::MainMenu::build()
{
}

void core::MainMenu::initGUI()
{
  m_gui.init("");
  m_gui.setFont("");
  m_gui.loadSheme("");

  CEGUI::Window *quitButton = static_cast<CEGUI::PushButton *>(
      m_gui.createButton("", glm::vec4(0.3f, 0.3f, 0.1f, 0.05f),
                         glm::vec4(0.0), "ExitButton"));
  quitButton->setText("QUIT");
  quitButton->subscribeEvent(
      CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&MainMenu::onExitClick, this));

  CEGUI::Window *playButton = static_cast<CEGUI::PushButton *>(
      m_gui.createButton("", glm::vec4(0.7f, 0.7f, 0.1f, 0.05f),
                         glm::vec4(0.0), "ExitButton"));
  playButton->setText("PLAY");
  playButton->subscribeEvent(
      CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&MainMenu::onPlayClick, this));
}

bool core::MainMenu::onExitClick(CEGUI::EventArgs const &e)
{
  m_curState = core::GameState::Quit;
  return true;
}

bool core::MainMenu::onPlayClick(CEGUI::EventArgs const &e)
{
  m_curState = core::GameState::InGame;
  return true;
}