//
// Created by duhieu_b on 31/05/17.
//

#include "MenuManager.hpp"
#include "MainMenu.hpp"

bool menu::MenuManager::keyPressed(OIS::KeyEvent const &ke)
{
  for (std::size_t l_i = m_gui.size(); l_i > 0; --l_i)
    {
      if (m_gui[l_i - 1]->keyPressed(ke))
	return true;
    }
  return false;
}

bool menu::MenuManager::keyReleased(OIS::KeyEvent const &ke)
{
  for (std::size_t l_i = m_gui.size(); l_i > 0; --l_i)
    {
      if (m_gui[l_i - 1]->keyReleased(ke))
	return true;
    }
  return false;
}

bool menu::MenuManager::mouseMoved(OIS::MouseEvent const &me)
{
  for (std::size_t l_i = m_gui.size(); l_i > 0; --l_i)
    {
      if (m_gui[l_i - 1]->mouseMoved(me))
	return true;
    }
  return false;
}

bool menu::MenuManager::mousePressed(OIS::MouseEvent const &me,
                                     OIS::MouseButtonID     id)
{
  for (std::size_t l_i = m_gui.size(); l_i > 0; --l_i)
    {
      if (m_gui[l_i - 1]->mousePressed(me, id))
	return true;
    }
  return false;
}

bool menu::MenuManager::mouseReleased(OIS::MouseEvent const &me,
                                      OIS::MouseButtonID     id)
{
  for (std::size_t l_i = m_gui.size(); l_i > 0; --l_i)
    {
      if (m_gui[l_i - 1]->mouseReleased(me, id))
	return true;
    }
  return false;
}

void menu::MenuManager::push(core::MenuState layer)
{
  m_gui.push(m_menuLayer[static_cast<std::size_t>(layer)].get());
}

void menu::MenuManager::popLayer()
{
  m_gui.pop();
}

menu::MenuManager::MenuManager(Ogre::RenderWindow *win)
    : m_sceneMan(Ogre::Root::getSingleton().createSceneManager(
          "DefaultSceneManager", "Menu scene manager")),
      m_camera(m_sceneMan->createCamera("MenuCamera")), m_viewport(nullptr),
      m_menuLayer({}), m_gui({})
{
  m_menuLayer[static_cast<size_t>(core::MenuState::MainMenu)] =
      std::make_unique<core::MainMenu>();
  /*m_menuLayer[static_cast<size_t>(core::MenuState::Option)] =
          std::make_unique<core::Option>();
  m_menuLayer[static_cast<size_t>(core::MenuState::Score] =
          std::make_unique<core::Score>();
  m_menuLayer[static_cast<size_t>(core::MenuState::SoloPlayerGame)] =
          std::make_unique<core::SoloPlayerGame>();
  m_menuLayer[static_cast<size_t>(core::MenuState::MultiPlayerGame)] =
          std::make_unique<core::MultiPlayerGame>();*/
  m_gui.push(
      m_menuLayer[static_cast<size_t>(core::MenuState::MainMenu)].get());
  m_camera->setPosition(Ogre::Vector3(0, 0, 0));
  m_camera->lookAt(Ogre::Vector3(0, 0, 0));
  m_camera->setNearClipDistance(2);
  m_viewport = win->addViewport(m_camera, 5);
  m_viewport->setOverlaysEnabled(false);
  m_viewport->setClearEveryFrame(true);
  m_viewport->setBackgroundColour(Ogre::ColourValue::Black);
  m_camera->setAspectRatio(Ogre::Real(m_viewport->getActualWidth()) /
                           Ogre::Real(m_viewport->getActualHeight()));
  m_gui[0]->entry();
}

core::IMenuLayer *menu::MenuManager::getMenuLayer()
{
  return m_gui[0];
}