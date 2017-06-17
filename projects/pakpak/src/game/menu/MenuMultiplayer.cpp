//
// Created by brout_m on 09/06/17.
//

#include "pakpak_stdafx.hpp"

namespace core
{
  MenuMultiplayer::MenuMultiplayer(menu::MenuManager &menuManager, GUI &gui,
                                   NetworkManager &net)
      : m_gui(gui), m_curState(GameState::Menu), m_menuManager(menuManager),
        m_network(net)

  {
    nope::log::Log(Debug) << "Building MenuMultiplayer";
  }

  void MenuMultiplayer::draw()
  {
  }

  void MenuMultiplayer::entry()
  {
    nope::log::Log(Debug) << "Entering MenuMultiplayer";

    m_network.authenticate();
    std::vector<GameServer> gameServerList = m_network.getServerList();

    for (GameServer &game : gameServerList)
      {
	nope::log::Log(Info)
	    << "Server: " << game.address << ":" << game.port << " [ "
	    << game.clients << " / " << game.maxClients << " ]";
      }

    m_gui.loadLayout("multiplayer.layout");
    m_gui.setCursorArrow("TaharezLook/MouseArrow");

    m_gui.getRoot()
        ->getChild("back_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuMultiplayer::onBackClick, this));

    m_gui.getRoot()
        ->getChild("launch_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuMultiplayer::onPlayClick, this));
  }

  void MenuMultiplayer::exit()
  {
    m_network.deauthenticate();
    // GameServer if connected
    nope::log::Log(Debug) << "Exit MenuMultiplayer";
  }

  void MenuMultiplayer::destroy()
  {
    exit();
    nope::log::Log(Debug) << "Destroying MenuMultiplayer";
  }

  GameState MenuMultiplayer::update() const
  {
    return m_curState;
  }

  void MenuMultiplayer::build()
  {
    nope::log::Log(Debug) << "Building MenuMultiplayer";
  }

  bool MenuMultiplayer::keyPressed(const OIS::KeyEvent &arg)
  {
    CEGUI::GUIContext &context =
        CEGUI::System::getSingleton().getDefaultGUIContext();
    context.injectKeyDown(static_cast<CEGUI::Key::Scan>(arg.key));
    context.injectChar(static_cast<CEGUI::Key::Scan>(arg.text));
    return true;
  }

  bool MenuMultiplayer::mouseMoved(const OIS::MouseEvent &arg)
  {
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseMove(static_cast<float>(arg.state.X.rel),
                         static_cast<float>(arg.state.Y.rel));
  }

  bool MenuMultiplayer::mousePressed(const OIS::MouseEvent &arg,
                                     OIS::MouseButtonID     id)
  {
    (void)arg;
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseButtonDown(convertButton(id));
  }

  bool MenuMultiplayer::mouseReleased(const OIS::MouseEvent &arg,
                                      OIS::MouseButtonID     id)
  {
    (void)arg;
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseButtonUp(convertButton(id));
  }

  bool MenuMultiplayer::keyReleased(const OIS::KeyEvent &arg)
  {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
        static_cast<CEGUI::Key::Scan>(arg.key));
    return true;
  }

  CEGUI::MouseButton
      MenuMultiplayer::convertButton(OIS::MouseButtonID buttonID)
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

  bool MenuMultiplayer::onBackClick(CEGUI::EventArgs const &)
  {
    exit();
    m_menuManager.popLayer();
    m_menuManager.begin();
    return false;
  }

  bool MenuMultiplayer::onPlayClick(CEGUI::EventArgs const &)
  {
    m_curState = GameState::InGame;
    m_gui.hideCursor();
    return true;
  }
}
