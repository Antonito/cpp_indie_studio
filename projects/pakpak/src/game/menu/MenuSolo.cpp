//
// Created by brout_m on 09/06/17.
//

#include "pakpak_stdafx.hpp"

namespace core
{
  MenuSolo::MenuSolo(menu::MenuManager &menuManager, GUI &gui,
                     SoundManager &sound, SettingsPlayer &settings)
      : m_gui(gui), m_curState(GameState::Menu), m_menuManager(menuManager),
        m_sound(sound), m_playerCount(1), m_settings(settings), m_curMap(0)
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
    if (!m_gui.getRoot()->getChild("right_button"))
      {
	throw GUIError("Missing asset right_button");
      }
    if (!m_gui.getRoot()->getChild("left_button"))
      {
	throw GUIError("Missing asset left_button");
      }
    if (!m_gui.getRoot()->getChild("map_holder"))
      {
	throw GUIError("Missing asset map_holder");
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
        ->getChild("left_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuSolo::onLeftClick, this));

    m_gui.getRoot()
        ->getChild("left_button")
        ->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,
                         CEGUI::Event::Subscriber(&MenuSolo::onArea, this));

    m_gui.getRoot()
        ->getChild("right_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuSolo::onRightClick, this));

    m_gui.getRoot()
        ->getChild("right_button")
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

  bool MenuSolo::mousePressed(const OIS::MouseEvent &, OIS::MouseButtonID id)
  {
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseButtonDown(convertButton(id));
  }

  bool MenuSolo::mouseReleased(const OIS::MouseEvent &, OIS::MouseButtonID id)
  {
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
    m_settings.setSelectedMap(static_cast<std::uint32_t>(m_curMap));
    return true;
  }

  static std::vector<std::string> gl_map = {"pakpak_map/one", "pakpak_map/two",
                                            "pakpak_map/three",
                                            "pakpak_map/four"};

  bool MenuSolo::onLeftClick(CEGUI::EventArgs const &)
  {
    soundClick();
    m_curMap = m_curMap - 1 < 0 ? static_cast<std::int32_t>(gl_map.size()) - 1
                                : m_curMap - 1;
    m_gui.getRoot()
        ->getChild("map_holder")
        ->setProperty("Image", gl_map[static_cast<std::size_t>(m_curMap)]);
    return true;
  }

  bool MenuSolo::onRightClick(CEGUI::EventArgs const &)
  {
    soundClick();
    m_curMap = m_curMap + 1 == static_cast<std::int32_t>(gl_map.size())
                   ? 0
                   : m_curMap + 1;
    m_gui.getRoot()
        ->getChild("map_holder")
        ->setProperty("Image", gl_map[static_cast<std::size_t>(m_curMap)]);
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

  std::int32_t MenuSolo::getSelectedMap() const
  {
    return m_curMap;
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
