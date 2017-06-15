//
// Created by brout_m on 09/06/17.
//

#include "pakpak_stdafx.hpp"

namespace core
{
  MenuKeymap::MenuKeymap(menu::MenuManager &menuManager, GUI &gui,
                         SettingsPlayer &settings)
      : m_gui(gui), m_curState(GameState::Menu), m_menuManager(menuManager),
        m_playerSelected(0), m_buttons(), m_settings(settings),
        m_listening(false), m_curKey(nullptr), m_curButton("")

  {
  }

  void MenuKeymap::draw()
  {
  }

  void MenuKeymap::entry()
  {
    m_gui.loadLayout("keymap.layout");
    m_gui.setCursorArrow("TaharezLook/MouseArrow");

    m_buttons[0] = m_gui.getRoot()->getChild("player1_button");
    m_buttons[1] = m_gui.getRoot()->getChild("player2_button");
    m_buttons[2] = m_gui.getRoot()->getChild("player3_button");
    m_buttons[3] = m_gui.getRoot()->getChild("player4_button");

    m_gui.getRoot()
        ->getChild("back_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuKeymap::onBackClick, this));

    m_gui.getRoot()
        ->getChild("up_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuKeymap::onUpClick, this));

    m_gui.getRoot()
        ->getChild("down_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuKeymap::onDownClick, this));

    m_gui.getRoot()
        ->getChild("left_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuKeymap::onLeftClick, this));

    m_gui.getRoot()
        ->getChild("right_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuKeymap::onRightClick, this));

    m_gui.getRoot()
        ->getChild("pause_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuKeymap::onPauseClick, this));

    m_gui.getRoot()
        ->getChild("use_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuKeymap::onUseClick, this));

    m_buttons[0]->subscribeEvent(
        CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(&MenuKeymap::onPlayer1Click, this));
    m_buttons[1]->subscribeEvent(
        CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(&MenuKeymap::onPlayer2Click, this));
    m_buttons[2]->subscribeEvent(
        CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(&MenuKeymap::onPlayer3Click, this));
    m_buttons[3]->subscribeEvent(
        CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(&MenuKeymap::onPlayer4Click, this));

    loadLayout(m_playerSelected);
  }

  void MenuKeymap::exit()
  {
  }

  void MenuKeymap::destroy()
  {
  }

  GameState MenuKeymap::update() const
  {
    return m_curState;
  }

  void MenuKeymap::build()
  {
  }

  bool MenuKeymap::keyPressed(const OIS::KeyEvent &arg)
  {
    if (m_listening)
      {
	m_listening = false;
	if (!m_settings.updateKey(static_cast<int>(m_playerSelected),
	                          *m_curKey, arg.key))
	  {
	    Log(nope::log::Error) << "Key already used";
	    return true;
	  }
	*m_curKey = arg.key;
	m_gui.getRoot()
	    ->getChild(m_curButton)
	    ->setProperty("Text", m_settings.getTextForKey(arg.key));

	Log(nope::log::Debug) << m_settings.getTextForKey(arg.key);
      }
    else
      {
	CEGUI::GUIContext &context =
	    CEGUI::System::getSingleton().getDefaultGUIContext();
	context.injectKeyDown((CEGUI::Key::Scan)arg.key);
	context.injectChar((CEGUI::Key::Scan)arg.text);
      }
    return true;
  }

  bool MenuKeymap::mouseMoved(const OIS::MouseEvent &arg)
  {
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseMove(static_cast<float>(arg.state.X.rel),
                         static_cast<float>(arg.state.Y.rel));
  }

  bool MenuKeymap::mousePressed(const OIS::MouseEvent &arg,
                                OIS::MouseButtonID     id)
  {
    (void)arg;
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseButtonDown(convertButton(id));
  }

  bool MenuKeymap::mouseReleased(const OIS::MouseEvent &arg,
                                 OIS::MouseButtonID     id)
  {
    (void)arg;
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseButtonUp(convertButton(id));
  }

  bool MenuKeymap::keyReleased(const OIS::KeyEvent &arg)
  {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
        (CEGUI::Key::Scan)arg.key);
    return true;
  }

  CEGUI::MouseButton MenuKeymap::convertButton(OIS::MouseButtonID buttonID)
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

  bool MenuKeymap::onBackClick(CEGUI::EventArgs const &)
  {
    m_menuManager.popLayer();
    m_menuManager.begin();
    return true;
  }

  bool MenuKeymap::onUpClick(CEGUI::EventArgs const &)
  {
    if (m_listening == false)
      {
	m_listening = true;
      }
    m_curKey = reinterpret_cast<OIS::KeyCode *>(
        &m_settings.getPlayer(static_cast<int>(m_playerSelected)).key.speedUp);
    m_curButton = "up_button";
    return true;
  }

  bool MenuKeymap::onDownClick(CEGUI::EventArgs const &)
  {
    if (m_listening == false)
      {
	m_listening = true;
      }
    m_curKey = reinterpret_cast<OIS::KeyCode *>(
        &m_settings.getPlayer(static_cast<int>(m_playerSelected))
             .key.slowDown);
    m_curButton = "down_button";
    return true;
  }

  bool MenuKeymap::onLeftClick(CEGUI::EventArgs const &)
  {
    if (m_listening == false)
      {
	m_listening = true;
      }
    m_curKey = reinterpret_cast<OIS::KeyCode *>(
        &m_settings.getPlayer(static_cast<int>(m_playerSelected))
             .key.turnLeft);
    m_curButton = "left_button";
    return true;
  }

  bool MenuKeymap::onRightClick(CEGUI::EventArgs const &)
  {
    if (m_listening == false)
      {
	m_listening = true;
      }
    m_curKey = reinterpret_cast<OIS::KeyCode *>(
        &m_settings.getPlayer(static_cast<int>(m_playerSelected))
             .key.turnRight);
    m_curButton = "right_button";
    return true;
  }

  bool MenuKeymap::onPauseClick(CEGUI::EventArgs const &)
  {
    if (m_listening == false)
      {
	m_listening = true;
      }
    m_curKey = reinterpret_cast<OIS::KeyCode *>(
        &m_settings.getPlayer(static_cast<int>(m_playerSelected))
             .key.openMenu);
    m_curButton = "pause_button";
    return true;
  }

  bool MenuKeymap::onUseClick(CEGUI::EventArgs const &)
  {
    if (m_listening == false)
      {
	m_listening = true;
      }
    m_curKey = reinterpret_cast<OIS::KeyCode *>(
        &m_settings.getPlayer(static_cast<int>(m_playerSelected))
             .key.useObject);
    m_curButton = "use_button";
    return true;
  }

  void MenuKeymap::swapButtons(size_t newSelected)
  {
    if (newSelected != m_playerSelected)
      {
	AssetSetter::setTextColor(*m_buttons[m_playerSelected],
	                          AssetSetter::TEXT_COLOR::TBLACK);
	AssetSetter::setButtonBack(*m_buttons[m_playerSelected],
	                           AssetSetter::BUTTON_COLOR::BGREY);

	m_playerSelected = newSelected;
	AssetSetter::setTextColor(*m_buttons[m_playerSelected],
	                          AssetSetter::TEXT_COLOR::TBLUE);
	AssetSetter::setButtonBack(*m_buttons[m_playerSelected],
	                           AssetSetter::BUTTON_COLOR::BGREEN);
      }
  }

  void MenuKeymap::loadLayout(size_t playerIndex)
  {
    m_gui.getRoot()
        ->getChild("up_button")
        ->setProperty("Text",
                      m_settings.getTextForKey(static_cast<OIS::KeyCode>(
                          m_settings.getPlayer(static_cast<int>(playerIndex))
                              .key.speedUp)));

    m_gui.getRoot()
        ->getChild("down_button")
        ->setProperty("Text",
                      m_settings.getTextForKey(static_cast<OIS::KeyCode>(
                          m_settings.getPlayer(static_cast<int>(playerIndex))
                              .key.slowDown)));

    m_gui.getRoot()
        ->getChild("left_button")
        ->setProperty("Text",
                      m_settings.getTextForKey(static_cast<OIS::KeyCode>(
                          m_settings.getPlayer(static_cast<int>(playerIndex))
                              .key.turnLeft)));

    m_gui.getRoot()
        ->getChild("right_button")
        ->setProperty("Text",
                      m_settings.getTextForKey(static_cast<OIS::KeyCode>(
                          m_settings.getPlayer(static_cast<int>(playerIndex))
                              .key.turnRight)));

    m_gui.getRoot()
        ->getChild("pause_button")
        ->setProperty("Text",
                      m_settings.getTextForKey(static_cast<OIS::KeyCode>(
                          m_settings.getPlayer(static_cast<int>(playerIndex))
                              .key.openMenu)));

    m_gui.getRoot()
        ->getChild("use_button")
        ->setProperty("Text",
                      m_settings.getTextForKey(static_cast<OIS::KeyCode>(
                          m_settings.getPlayer(static_cast<int>(playerIndex))
                              .key.useObject)));
  }

  bool MenuKeymap::onPlayer1Click(CEGUI::EventArgs const &)
  {
    swapButtons(0);
    loadLayout(m_playerSelected);
    return true;
  }

  bool MenuKeymap::onPlayer2Click(CEGUI::EventArgs const &)
  {
    swapButtons(1);
    loadLayout(m_playerSelected);
    return true;
  }

  bool MenuKeymap::onPlayer3Click(CEGUI::EventArgs const &)
  {
    swapButtons(2);
    loadLayout(m_playerSelected);
    return true;
  }

  bool MenuKeymap::onPlayer4Click(CEGUI::EventArgs const &)
  {
    swapButtons(3);
    loadLayout(m_playerSelected);
    return true;
  }
}