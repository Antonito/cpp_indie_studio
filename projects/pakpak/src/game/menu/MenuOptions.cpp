//
// Created by brout_m on 09/06/17.
//

#include <game/menu/MenuOptions.hpp>
#include "pakpak_stdafx.hpp"

namespace core
{
  MenuOptions::MenuOptions(menu::MenuManager &menuManager, GUI &gui,
                           SoundManager &sound)
      : m_gui(gui), m_curState(GameState::Menu), m_menuManager(menuManager),
        m_volumeButtons(), m_graphicButtons(), m_graphicSelected(0),
        m_sound(sound),
        m_volumeSelected(static_cast<std::size_t>(m_sound.getVolume() * 4.0f))
  {
    nope::log::Log(Debug) << "Initialization Current Volume : "
                          << static_cast<std::size_t>(m_sound.getVolume() *
                                                      4.0f);
  }

  void MenuOptions::draw()
  {
  }

  void MenuOptions::entry()
  {
    m_gui.loadLayout("options.layout");
    m_gui.setCursorArrow("TaharezLook/MouseArrow");

    m_graphicSelected = 0;
    nope::log::Log(Debug) << "Current Volume : " << m_sound.getVolume();
    m_volumeSelected = 4;
    if (!(m_volumeButtons[0] = m_gui.getRoot()->getChild("volume/level_0")))
      {
	throw GUIError("Missing asset volume/level_0");
      }
    if (!(m_volumeButtons[1] = m_gui.getRoot()->getChild("volume/level_25")))
      {
	throw GUIError("Missing asset volume/level_25");
      }
    if (!(m_volumeButtons[2] = m_gui.getRoot()->getChild("volume/level_50")))
      {
	throw GUIError("Missing asset volume/level_50");
      }
    if (!(m_volumeButtons[3] = m_gui.getRoot()->getChild("volume/level_75")))
      {
	throw GUIError("Missing asset volume/level_75");
      }
    if (!(m_volumeButtons[4] = m_gui.getRoot()->getChild("volume/level_100")))
      {
	throw GUIError("Missing asset volume/level_100");
      }
    if (!(m_graphicButtons[0] = m_gui.getRoot()->getChild("windowed_button")))
      {
	throw GUIError("Missing asset windowed_button");
      }
    if (!(m_graphicButtons[1] =
              m_gui.getRoot()->getChild("fullscreen_button")))
      {
	throw GUIError("Missing asset fullscreen_button");
      }
    if (!(m_gui.getRoot()->getChild("back_button")))
      {
	throw GUIError("Missing asset back_button");
      }
    if (!(m_gui.getRoot()->getChild("edit_button")))
      {
	throw GUIError("Missing asset edit_button");
      }
    size_t newVolume = static_cast<std::size_t>(m_sound.getVolume() * 4.0f);
    swapButtons(m_volumeButtons, m_volumeSelected, newVolume,
                AssetSetter::greyButton, AssetSetter::redButton);

    m_gui.getRoot()
        ->getChild("back_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuOptions::onBackClick, this));

    m_gui.getRoot()
        ->getChild("back_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventMouseEntersArea,
            CEGUI::Event::Subscriber(&MenuOptions::onBackArea, this));

    m_gui.getRoot()
        ->getChild("edit_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuOptions::onKeymapEdit, this));

    m_gui.getRoot()
        ->getChild("edit_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventMouseEntersArea,
            CEGUI::Event::Subscriber(&MenuOptions::onKeymapEditArea, this));

    m_volumeButtons[0]->subscribeEvent(
        CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(&MenuOptions::onVolumeLevel0, this));
    m_volumeButtons[0]->subscribeEvent(
        CEGUI::PushButton::EventMouseEntersArea,
        CEGUI::Event::Subscriber(&MenuOptions::onVolumeLevel0Pass, this));

    m_volumeButtons[1]->subscribeEvent(
        CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(&MenuOptions::onVolumeLevel25, this));
    m_volumeButtons[1]->subscribeEvent(
        CEGUI::PushButton::EventMouseEntersArea,
        CEGUI::Event::Subscriber(&MenuOptions::onVolumeLevel25Pass, this));

    m_volumeButtons[2]->subscribeEvent(
        CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(&MenuOptions::onVolumeLevel50, this));
    m_volumeButtons[2]->subscribeEvent(
        CEGUI::PushButton::EventMouseEntersArea,
        CEGUI::Event::Subscriber(&MenuOptions::onVolumeLevel50Pass, this));

    m_volumeButtons[3]->subscribeEvent(
        CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(&MenuOptions::onVolumeLevel75, this));
    m_volumeButtons[3]->subscribeEvent(
        CEGUI::PushButton::EventMouseEntersArea,
        CEGUI::Event::Subscriber(&MenuOptions::onVolumeLevel75Pass, this));

    m_volumeButtons[4]->subscribeEvent(
        CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(&MenuOptions::onVolumeLevel100, this));
    m_volumeButtons[4]->subscribeEvent(
        CEGUI::PushButton::EventMouseEntersArea,
        CEGUI::Event::Subscriber(&MenuOptions::onVolumeLevel100Pass, this));

    m_graphicButtons[0]->subscribeEvent(
        CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(&MenuOptions::onLowClick, this));
    m_volumeButtons[0]->subscribeEvent(
        CEGUI::PushButton::EventMouseEntersArea,
        CEGUI::Event::Subscriber(&MenuOptions::onLowPass, this));

    m_graphicButtons[1]->subscribeEvent(
        CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(&MenuOptions::onHighClick, this));
    m_volumeButtons[1]->subscribeEvent(
        CEGUI::PushButton::EventMouseEntersArea,
        CEGUI::Event::Subscriber(&MenuOptions::onHighPass, this));
  }

  void MenuOptions::exit()
  {
  }

  void MenuOptions::destroy()
  {
  }

  GameState MenuOptions::update() const
  {
    return m_curState;
  }

  void MenuOptions::build()
  {
  }

  bool MenuOptions::keyPressed(const OIS::KeyEvent &arg)
  {
    CEGUI::GUIContext &context =
        CEGUI::System::getSingleton().getDefaultGUIContext();
    context.injectKeyDown(static_cast<CEGUI::Key::Scan>(arg.key));
    context.injectChar(static_cast<CEGUI::Key::Scan>(arg.text));
    return true;
  }

  bool MenuOptions::mouseMoved(const OIS::MouseEvent &arg)
  {
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseMove(static_cast<float>(arg.state.X.rel),
                         static_cast<float>(arg.state.Y.rel));
  }

  bool MenuOptions::mousePressed(const OIS::MouseEvent &arg,
                                 OIS::MouseButtonID     id)
  {
    (void)arg;
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseButtonDown(convertButton(id));
  }

  bool MenuOptions::mouseReleased(const OIS::MouseEvent &arg,
                                  OIS::MouseButtonID     id)
  {
    (void)arg;
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseButtonUp(convertButton(id));
  }

  bool MenuOptions::keyReleased(const OIS::KeyEvent &arg)
  {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
        static_cast<CEGUI::Key::Scan>(arg.key));
    return true;
  }

  CEGUI::MouseButton MenuOptions::convertButton(OIS::MouseButtonID buttonID)
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

  bool MenuOptions::onBackClick(CEGUI::EventArgs const &)
  {
    soundClick();
    m_sound.playSound(core::ESound::BACK_RACE_SOUND);
    m_menuManager.popLayer();
    m_menuManager.begin();
    return false;
  }

  bool MenuOptions::onBackArea(CEGUI::EventArgs const &)
  {
    soundPass();
    return false;
  }

  bool MenuOptions::onKeymapEdit(CEGUI::EventArgs const &)
  {
    soundClick();
    m_menuManager.push(MenuState::Keymap);
    m_menuManager.begin();
    return true;
  }

  bool MenuOptions::onKeymapEditArea(CEGUI::EventArgs const &)
  {
    soundPass();
    return true;
  }

  void MenuOptions::swapButtons(CEGUI::Window **tab, size_t &old,
                                size_t                          newSelected,
                                AssetSetter::ButtonStyle const &unselected,
                                AssetSetter::ButtonStyle const &selected)
  {
    if (newSelected != old)
      {
	AssetSetter::setTextColor(*tab[old], unselected.text);
	AssetSetter::setButtonBack(*tab[old], unselected.button);
	old = newSelected;
	AssetSetter::setTextColor(*tab[old], selected.text);
	AssetSetter::setButtonBack(*tab[old], selected.button);
      }
  }

  bool MenuOptions::onVolumeLevel0(CEGUI::EventArgs const &)
  {
    soundClick();
    m_sound.setVolume(0.0f);
    swapButtons(m_volumeButtons, m_volumeSelected, 0, AssetSetter::greyButton,
                AssetSetter::redButton);
    return true;
  }

  bool MenuOptions::onVolumeLevel25(CEGUI::EventArgs const &)
  {
    soundClick();
    m_sound.setVolume(0.25f);
    swapButtons(m_volumeButtons, m_volumeSelected, 1, AssetSetter::greyButton,
                AssetSetter::redButton);
    return true;
  }

  bool MenuOptions::onVolumeLevel50(CEGUI::EventArgs const &)
  {
    soundClick();
    m_sound.setVolume(0.50f);
    swapButtons(m_volumeButtons, m_volumeSelected, 2, AssetSetter::greyButton,
                AssetSetter::redButton);
    return true;
  }

  bool MenuOptions::onVolumeLevel75(CEGUI::EventArgs const &)
  {
    soundClick();
    m_sound.setVolume(0.75f);
    swapButtons(m_volumeButtons, m_volumeSelected, 3, AssetSetter::greyButton,
                AssetSetter::redButton);
    return true;
  }

  bool MenuOptions::onVolumeLevel100(CEGUI::EventArgs const &)
  {
    soundClick();
    m_sound.setVolume(1.0f);
    swapButtons(m_volumeButtons, m_volumeSelected, 4, AssetSetter::greyButton,
                AssetSetter::redButton);
    return true;
  }

  bool MenuOptions::onVolumeLevel0Pass(CEGUI::EventArgs const &)
  {
    soundPass();
    return true;
  }

  bool MenuOptions::onVolumeLevel25Pass(CEGUI::EventArgs const &)
  {
    soundPass();
    return true;
  }

  bool MenuOptions::onVolumeLevel50Pass(CEGUI::EventArgs const &)
  {
    soundPass();
    return true;
  }

  bool MenuOptions::onVolumeLevel75Pass(CEGUI::EventArgs const &)
  {
    soundPass();
    return true;
  }

  bool MenuOptions::onVolumeLevel100Pass(CEGUI::EventArgs const &)
  {
    soundPass();
    return true;
  }

  bool MenuOptions::onLowClick(CEGUI::EventArgs const &)
  {
    soundClick();
    swapButtons(m_graphicButtons, m_graphicSelected, 0,
                AssetSetter::greyButton, AssetSetter::yellowButton);
    return true;
  }

  bool MenuOptions::onLowPass(CEGUI::EventArgs const &)
  {
    soundPass();
    return true;
  }

  bool MenuOptions::onHighClick(CEGUI::EventArgs const &)
  {
    soundClick();
    swapButtons(m_graphicButtons, m_graphicSelected, 1,
                AssetSetter::greyButton, AssetSetter::yellowButton);
    return true;
  }

  bool MenuOptions::onHighPass(CEGUI::EventArgs const &)
  {
    soundPass();
    return true;
  }

  void MenuOptions::soundClick()
  {
    m_sound.playSound(core::ESound::CLICK_BUTTON);
  }

  void MenuOptions::soundPass()
  {
    m_sound.playSound(core::ESound::PASS_BUTTON);
  }
}
