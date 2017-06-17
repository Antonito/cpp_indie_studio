#include "pakpak_stdafx.hpp"

namespace menu
{
  ContextMenu::ContextMenu(Ogre::RenderWindow *win, core::InputListener *input,
                           core::SettingsPlayer &settings, core::SoundManager &sound)
      : core::AContext(win, input), m_menu(win, settings, sound), m_settings(settings), m_sound(sound)
  {
  }

  ContextMenu::~ContextMenu()
  {
  }

  void ContextMenu::enable()
  {
    m_sound.loadSound("deps/indie_resource/songs/theme.wav");
    m_sound.playSound();
    m_sound.loopSound();
    m_input->setMouseEventCallback(this);
    m_input->setKeyboardEventCallback(this);

    m_menu.begin();
  }

  void ContextMenu::disable()
  {
    m_sound.stopSound();
    m_sound.clear();
    m_menu.end();
  }

  core::GameState ContextMenu::update()
  {
    m_input->capture();
    return m_menu.getMenuLayer()->update();
  }

  void ContextMenu::display()
  {
    m_menu.getMenuLayer()->draw();
  }

  bool ContextMenu::keyPressed(const OIS::KeyEvent &arg)
  {
    m_menu.keyPressed(arg);
    return true;
  }

  bool ContextMenu::keyReleased(const OIS::KeyEvent &arg)
  {
    m_menu.keyReleased(arg);
    return true;
  }

  bool ContextMenu::mouseMoved(const OIS::MouseEvent &arg)
  {
    m_menu.mouseMoved(arg);
    return true;
  }

  bool ContextMenu::mousePressed(const OIS::MouseEvent &arg,
                                 OIS::MouseButtonID     id)
  {
    m_menu.mousePressed(arg, id);
    return true;
  }

  bool ContextMenu::mouseReleased(const OIS::MouseEvent &arg,
                                  OIS::MouseButtonID     id)
  {
    m_menu.mouseReleased(arg, id);
    return false;
  }
}
