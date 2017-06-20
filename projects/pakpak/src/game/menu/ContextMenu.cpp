#include "pakpak_stdafx.hpp"

namespace menu
{
  ContextMenu::ContextMenu(Ogre::RenderWindow *win, core::InputListener *input,
                           core::SettingsPlayer &settings,
                           core::SoundManager &  sound,
                           core::NetworkManager &net)
      : core::AContext(win, input), m_menu(win, settings, sound, net),
        m_sound(sound)
  {
  }

  ContextMenu::~ContextMenu()
  {
  }

  void ContextMenu::enable()
  {
    nope::log::Log(Debug) << "\n***********************\n"
                          << "**Enable context menu**\n"
                          << "***********************\n";
    m_sound.playSound(core::ESound::THEME_SONG);
    m_sound.loopSound(core::ESound::THEME_SONG);
    m_sound.setVolumeSource(core::ESound::THEME_SONG,
                            0.25f * m_sound.getVolume());
    m_input->setMouseEventCallback(this);
    m_input->setKeyboardEventCallback(this);

    m_menu.begin();
  }

  void ContextMenu::disable()
  {
    nope::log::Log(Debug) << "\n***********************\n"
                          << "**Disable context menu**\n"
                          << "***********************\n";
    m_sound.stopSound(core::ESound::THEME_SONG);
    m_menu.end();
  }

  core::GameState ContextMenu::update()
  {
    m_menu.update();
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
