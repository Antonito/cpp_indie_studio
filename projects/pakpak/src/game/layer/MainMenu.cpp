#include "MainMenu.hpp"

void core::MainMenu::draw()
{
  m_gui.draw();
}

void core::MainMenu::entry()
{
  // TODO : INIT Camera

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

  CEGUI::PushButton *quitButton = static_cast<CEGUI::PushButton *>(
      m_gui.createButton("", glm::vec4(0.3f, 0.3f, 0.1f, 0.05f),
                         glm::vec4(0.0), "ExitButton"));
  quitButton->setText("QUIT");
  quitButton->suscribeEvent(
      CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&MainMenu::onExitClick, this));

  CEGUI::PlayButton *playButton = static_cast<CEGUI::PushButton *>(
      m_gui.createButton("", glm::vec4(0.7f, 0.7f, 0.1f, 0.05f),
                         glm::vec4(0.0), "ExitButton"));
  quitButton->setText("PLAY");
  quitButton->suscribeEvent(
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