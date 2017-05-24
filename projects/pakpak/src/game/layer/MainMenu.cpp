#include "MainMenu.hpp"

core::GameState core::MainMenu::changeScreen() const
{
    return core::GameState::InGame;
}

void core::MainMenu::draw()
{

}

void core::MainMenu::entry()
{
    //TODO : INIT Camera

    initGUI();
}

void core::MainMenu::exit()
{

}

void core::MainMenu::destroy()
{

}

void core::MainMenu::update()
{

}

void core::MainMenu::build()
{

}

void core::MainMenu::initGUI()
{
    m_gui.init("");
    m_gui.setFont("");
    m_gui.loadSheme("");
}
