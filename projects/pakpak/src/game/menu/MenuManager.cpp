//
// Created by duhieu_b on 31/05/17.
//

#include "game/menu/MenuSolo.hpp"
#include "game/menu/MenuMultiplayer.hpp"
#include "game/menu/MenuManager.hpp"
#include "game/menu/MainMenu.hpp"
#include "game/menu/MenuOptions.hpp"
#include "game/menu/MenuKeymap.hpp"

bool menu::MenuManager::keyPressed(OIS::KeyEvent const &ke)
{
  for (std::size_t l_i = m_layers.size(); l_i > 0; --l_i)
    {
      if (m_layers[l_i - 1]->keyPressed(ke))
	return true;
    }
  return false;
}

bool menu::MenuManager::keyReleased(OIS::KeyEvent const &ke)
{
  for (std::size_t l_i = m_layers.size(); l_i > 0; --l_i)
    {
      if (m_layers[l_i - 1]->keyReleased(ke))
	return true;
    }
  return false;
}

bool menu::MenuManager::mouseMoved(OIS::MouseEvent const &me)
{
  for (std::size_t l_i = m_layers.size(); l_i > 0; --l_i)
    {
      if (m_layers[l_i - 1]->mouseMoved(me))
	return true;
    }
  return false;
}

bool menu::MenuManager::mousePressed(OIS::MouseEvent const &me,
                                     OIS::MouseButtonID     id)
{
  for (std::size_t l_i = m_layers.size(); l_i > 0; --l_i)
    {
      if (m_layers[l_i - 1]->mousePressed(me, id))
	return true;
    }
  return false;
}

bool menu::MenuManager::mouseReleased(OIS::MouseEvent const &me,
                                      OIS::MouseButtonID     id)
{
  for (std::size_t l_i = m_layers.size(); l_i > 0; --l_i)
    {
      if (m_layers[l_i - 1]->mouseReleased(me, id))
	return true;
    }
  return false;
}

void menu::MenuManager::push(core::MenuState layer)
{
  m_layers.push(m_menuLayer[static_cast<std::size_t>(layer)].get());
}

void menu::MenuManager::popLayer()
{
  m_layers.pop();
}

menu::MenuManager::MenuManager(Ogre::RenderWindow *win)
    : m_sceneMan(Ogre::Root::getSingleton().createSceneManager(
          "DefaultSceneManager", "Menu scene manager")),
      m_camera(m_sceneMan->createCamera("MenuCamera")), m_viewport(nullptr),
      m_gui(), m_menuLayer({}), m_layers({})
{
  m_menuLayer[static_cast<size_t>(core::MenuState::MainMenu)] =
      std::make_unique<core::MainMenu>(*this, m_gui);
  m_menuLayer[static_cast<size_t>(core::MenuState::Option)] =
      std::make_unique<core::MenuOptions>(*this, m_gui);
  m_menuLayer[static_cast<size_t>(core::MenuState::Keymap)] =
      std::make_unique<core::MenuKeymap>(*this, m_gui);
  m_menuLayer[static_cast<size_t>(core::MenuState::SoloPlayerGame)] =
          std::make_unique<core::MenuSolo>(*this, m_gui);
  m_menuLayer[static_cast<size_t>(core::MenuState::MultiPlayerGame)] =
          std::make_unique<core::MenuMultiplayer>(*this, m_gui); /*
  m_menuLayer[static_cast<size_t>(core::MenuState::MultiPlayerGame)] =
          std::make_unique<core::MultiPlayerGame>();
          */
  m_layers.push(
      m_menuLayer[static_cast<size_t>(core::MenuState::MainMenu)].get());
  (void)win;
}

void menu::MenuManager::begin()
{
  m_layers[m_layers.size() - 1]->entry();
}

void menu::MenuManager::end()
{
  int size = static_cast<int>(m_layers.size());

  while (size > 0)
  {
    m_layers[size - 1]->destroy();
    m_layers.pop();
    --size;
  }
}

core::IMenuLayer *menu::MenuManager::getMenuLayer()
{
  return m_layers[m_layers.size() - 1];
}