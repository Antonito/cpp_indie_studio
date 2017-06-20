//
// Created by brout_m on 09/06/17.
//

#include "pakpak_stdafx.hpp"

namespace core
{
  MenuSolo::MenuSolo(menu::MenuManager &menuManager, GUI &gui,
                     SoundManager &sound, SettingsPlayer &settings)
      : m_gui(gui), m_curState(GameState::Menu), m_menuManager(menuManager),
        m_sound(sound), m_playerCount(1), m_settings(settings)
  {
  }

  void MenuSolo::draw()
  {
  }

  void MenuSolo::entry()
  {
    m_gui.loadLayout("soloplayer.layout");
    m_gui.setCursorArrow("TaharezLook/MouseArrow");
    setButtonText("soloplayers_button");
    m_curState = GameState::Menu;

    if (!m_gui.getRoot()->getChild("back_button"))
      {
	throw GUIError("Missing asset back_button");
      }
    if (!m_gui.getRoot()->getChild("play_button"))
      {
	throw GUIError("Missing asset play_button");
      }
    if (!m_gui.getRoot()->getChild("easy_button"))
      {
	throw GUIError("Missing asset easy_button");
      }
    if (!m_gui.getRoot()->getChild("hard_button"))
      {
	throw GUIError("Missing asset hard_button");
      }
    m_gui.getRoot()
        ->getChild("back_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuSolo::onBackClick, this));

    m_gui.getRoot()
        ->getChild("back_button")
        ->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,
                         CEGUI::Event::Subscriber(&MenuSolo::onArea, this));

    m_gui.getRoot()
        ->getChild("play_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuSolo::onPlayClick, this));

    m_gui.getRoot()
        ->getChild("play_button")
        ->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,
                         CEGUI::Event::Subscriber(&MenuSolo::onArea, this));

    m_gui.getRoot()
        ->getChild("easy_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuSolo::onEasyClick, this));

    m_gui.getRoot()
        ->getChild("easy_button")
        ->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,
                         CEGUI::Event::Subscriber(&MenuSolo::onArea, this));

    m_gui.getRoot()
        ->getChild("hard_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuSolo::onHardClick, this));

    m_gui.getRoot()
        ->getChild("hard_button")
        ->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,
                         CEGUI::Event::Subscriber(&MenuSolo::onArea, this));

    m_gui.getRoot()
        ->getChild("soloplayers_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuSolo::onPlayersClick, this));

    m_gui.getRoot()
        ->getChild("soloplayers_button")
        ->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,
                         CEGUI::Event::Subscriber(&MenuSolo::onArea, this));
  }

  void MenuSolo::exit()
  {
  }

  void MenuSolo::destroy()
  {
  }

  GameState MenuSolo::update() const
  {
    return m_curState;
  }

  void MenuSolo::build()
  {
  }

  bool MenuSolo::keyPressed(const OIS::KeyEvent &arg)
  {
    CEGUI::GUIContext &context =
        CEGUI::System::getSingleton().getDefaultGUIContext();
    context.injectKeyDown(static_cast<CEGUI::Key::Scan>(arg.key));
    context.injectChar(static_cast<CEGUI::Key::Scan>(arg.text));
    return true;
  }

  bool MenuSolo::mouseMoved(const OIS::MouseEvent &arg)
  {
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseMove(static_cast<float>(arg.state.X.rel),
                         static_cast<float>(arg.state.Y.rel));
  }

  bool MenuSolo::mousePressed(const OIS::MouseEvent &arg,
                              OIS::MouseButtonID     id)
  {
    (void)arg;
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseButtonDown(convertButton(id));
  }

  bool MenuSolo::mouseReleased(const OIS::MouseEvent &arg,
                               OIS::MouseButtonID     id)
  {
    (void)arg;
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseButtonUp(convertButton(id));
  }

  bool MenuSolo::keyReleased(const OIS::KeyEvent &arg)
  {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
        static_cast<CEGUI::Key::Scan>(arg.key));
    return true;
  }

  CEGUI::MouseButton MenuSolo::convertButton(OIS::MouseButtonID buttonID)
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

  bool MenuSolo::onBackClick(CEGUI::EventArgs const &)
  {
    soundClick();
    m_sound.playSound(core::ESound::BACK_RACE_SOUND);
    m_menuManager.popLayer();
    m_menuManager.begin();
    return false;
  }

  bool MenuSolo::onPlayClick(CEGUI::EventArgs const &)
  {
    soundClick();
    m_sound.playSound(core::ESound::GO_RACE_SOUND);
    m_curState = GameState::InGame;
    m_gui.hideCursor();
    m_settings.setPlayerCount(m_playerCount);
    return true;
  }

  bool MenuSolo::onEasyClick(CEGUI::EventArgs const &)
  {
    CEGUI::Window &easyButton = *m_gui.getRoot()->getChild("easy_button");
    CEGUI::Window &hardButton = *m_gui.getRoot()->getChild("hard_button");

    soundClick();
    AssetSetter::setButtonBack(easyButton, AssetSetter::BUTTON_COLOR::BYELLOW);
    AssetSetter::setTextColor(easyButton, AssetSetter::TEXT_COLOR::TRED);

    AssetSetter::setButtonBack(hardButton, AssetSetter::BUTTON_COLOR::BGREY);
    AssetSetter::setTextColor(hardButton, AssetSetter::TEXT_COLOR::TBLACK);
    return true;
  }

  bool MenuSolo::onHardClick(CEGUI::EventArgs const &)
  {
    CEGUI::Window &easyButton = *m_gui.getRoot()->getChild("easy_button");
    CEGUI::Window &hardButton = *m_gui.getRoot()->getChild("hard_button");

    soundClick();
    AssetSetter::setButtonBack(hardButton, AssetSetter::BUTTON_COLOR::BYELLOW);
    AssetSetter::setTextColor(hardButton, AssetSetter::TEXT_COLOR::TRED);

    AssetSetter::setButtonBack(easyButton, AssetSetter::BUTTON_COLOR::BGREY);
    AssetSetter::setTextColor(easyButton, AssetSetter::TEXT_COLOR::TBLACK);
    return true;
  }
  bool MenuSolo::onArea(const CEGUI::EventArgs &)
  {
    soundPass();
    return true;
  }

  void MenuSolo::soundPass()
  {
    m_sound.playSound(core::ESound::PASS_BUTTON);
  }

  void MenuSolo::soundClick()
  {
    m_sound.playSound(core::ESound::CLICK_BUTTON);
  }

  bool MenuSolo::onPlayersClick(CEGUI::EventArgs const &)
  {
    soundClick();
    m_playerCount = m_playerCount + 1u > 4u ? 1u : m_playerCount + 1u;
    setButtonText("soloplayers_button");
    return true;
  }

  void MenuSolo::setButtonText(std::string const &buttonName)
  {
    CEGUI::PushButton *button = static_cast<CEGUI::PushButton *>(
        m_gui.getRoot()->getChildRecursive(buttonName));

    if (button)
      {
	switch (m_playerCount)
	  {
	  case (2):
	    button->setText("2");
	    break;
	  case (3):
	    button->setText("3");
	    break;
	  case (4):
	    button->setText("4");
	    break;
	  default:
	    button->setText("1");
	  }
      }
  }
}
