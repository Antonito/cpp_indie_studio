//
// Created by brout_m on 09/06/17.
//

#include "pakpak_stdafx.hpp"

namespace core
{
  MenuMultiplayer::MenuMultiplayer(menu::MenuManager &menuManager, GUI &gui,
                                   SoundManager &sound, NetworkManager &net)
      : m_gui(gui), m_curState(GameState::Menu), m_menuManager(menuManager),
        m_sound(sound), m_selectGameServer(), m_network(net)
  {
    nope::log::Log(Debug) << "Building MenuMultiplayer";
  }

  void MenuMultiplayer::draw()
  {
  }

  void MenuMultiplayer::entry()
  {
    nope::log::Log(Debug) << "Entering MenuMultiplayer";

    m_gui.loadLayout("multiplayer.layout");
    m_gui.setCursorArrow("TaharezLook/MouseArrow");
    m_curState = GameState::Menu;

    m_network.authenticate();
    std::vector<GameServer> gameServerList = m_network.getServerList();

    nope::log::Log(Debug) << "Server list OKAY";

    if (!(m_gui.getRoot()->getChild("servers_list")))
      {
	throw std::exception();
	// TODO:Arthur find exception for button assets missing.
      }
    if (!(m_gui.getRoot()->getChild("back_button")))
      {
	throw std::exception();
	// TODO:Arthur find exception for button assets missing.
      }
    if (!(m_gui.getRoot()->getChild("launch_button")))
      {
	throw std::exception();
	// TODO:Arthur find exception for button assets missing.
      }
    static_cast<CEGUI::ItemListbox *>(
        m_gui.getRoot()->getChild("servers_list"))
        ->setAutoResizeEnabled(1);
    std::int32_t i(0);
    nope::log::Log(Debug) << "Entry on MultiMenu";
    CEGUI::WindowManager *winManager = CEGUI::WindowManager::getSingletonPtr();
    for (GameServer &game : gameServerList)
      {
	nope::log::Log(Debug)
	    << "List server : "
	    << "Server #" + std::to_string(i + 1) + " : " + game.address +
	           " Player : (" + std::to_string(game.clients) + "/" +
	           std::to_string(game.maxClients) + ").";
	nope::log::Log(Info) << "Server: " << game.address << ":" << game.port
	                     << " [ " << game.clients << " / "
	                     << game.maxClients << " ]";
	CEGUI::ItemEntry *itm = static_cast<CEGUI::ItemEntry *>(
	    winManager->createWindow("TaharezLook/ListboxItem"));
	itm->setText("Server #" + std::to_string(i + 1) + " : " +
	             game.address + " Player : (" +
	             std::to_string(game.clients) + "/" +
	             std::to_string(game.maxClients) + ").");
	static_cast<CEGUI::ItemListbox *>(
	    m_gui.getRoot()->getChild("servers_list"))
	    ->addItem(itm);
	i++;
      }

    for (std::int32_t j(0); j < (20 - i); ++j)
      {
	CEGUI::ItemEntry *itm = static_cast<CEGUI::ItemEntry *>(
	    winManager->createWindow("TaharezLook/ListboxItem"));
	itm->disable();
	static_cast<CEGUI::ItemListbox *>(
	    m_gui.getRoot()->getChild("servers_list"))
	    ->addItem(itm);
      }
    m_gui.getRoot()
        ->getChild("back_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuMultiplayer::onBackClick, this));

    m_gui.getRoot()
        ->getChild("back_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventMouseEntersArea,
            CEGUI::Event::Subscriber(&MenuMultiplayer::onBackArea, this));

    m_gui.getRoot()
        ->getChild("launch_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&MenuMultiplayer::onPlayClick, this));

    m_gui.getRoot()
        ->getChild("launch_button")
        ->subscribeEvent(
            CEGUI::PushButton::EventMouseEntersArea,
            CEGUI::Event::Subscriber(&MenuMultiplayer::onPlayArea, this));

    m_gui.getRoot()
        ->getChild("servers_list")
        ->subscribeEvent(
            CEGUI::ItemListbox::EventSelectionChanged,
            CEGUI::Event::Subscriber(&MenuMultiplayer::getServerPos, this));
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

  bool MenuMultiplayer::mousePressed(const OIS::MouseEvent &,
                                     OIS::MouseButtonID id)
  {
    return CEGUI::System::getSingleton()
        .getDefaultGUIContext()
        .injectMouseButtonDown(convertButton(id));
  }

  bool MenuMultiplayer::mouseReleased(const OIS::MouseEvent &,
                                      OIS::MouseButtonID id)
  {
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
    soundClick();
    exit();
    m_menuManager.popLayer();
    m_menuManager.begin();
    return false;
  }

  bool MenuMultiplayer::onPlayClick(CEGUI::EventArgs const &)
  {
    soundClick();

    // Get token from gameServer
    try
      {
	std::string const &token = m_network.getToken(m_selectGameServer);
	// Connect to game server
	m_network.connect(m_selectGameServer, token);
      }
    catch (...)
      {
	nope::log::Log(Debug)
	    << "\n======================================================\n=="
	       "Error cannot connect to the ConnectServerManager "
	       "!==\n======================================================";
	m_menuManager.push(MenuState::PopError);
	m_menuManager.begin();
	return true;
      }
    nope::log::Log(Debug) << "CONNECT TO GAME_SERVER CLEAN";
    m_curState = GameState::InGame;
    m_gui.hideCursor();
    return true;
  }

  void MenuMultiplayer::soundPass()
  {
    m_sound.playSound(core::ESound::PASS_BUTTON);
  }

  void MenuMultiplayer::soundClick()
  {
    m_sound.playSound(core::ESound::CLICK_BUTTON);
  }

  bool MenuMultiplayer::onBackArea(CEGUI::EventArgs const &)
  {
    soundPass();
    return true;
  }

  bool MenuMultiplayer::onPlayArea(CEGUI::EventArgs const &)
  {
    soundPass();
    return true;
  }

  bool MenuMultiplayer::getServerPos(CEGUI::EventArgs const &)
  {
    nope::log::Log(Debug) << "Selecting SERVVVVV";
    if (static_cast<CEGUI::ItemListbox *>(
            m_gui.getRoot()->getChild("servers_list"))
            ->getFirstSelectedItem() != NULL)
      {
	nope::log::Log(Debug)
	    << "Select a specific server network : "
	    << static_cast<CEGUI::ItemListbox *>(
	           m_gui.getRoot()->getChild("servers_list"))
	           ->getItemIndex(
	               static_cast<CEGUI::ItemListbox *>(
	                   m_gui.getRoot()->getChild("servers_list"))
	                   ->getFirstSelectedItem());
	m_selectGameServer =
	    m_network
	        .getServerList()[static_cast<CEGUI::ItemListbox *>(
	                             m_gui.getRoot()->getChild("servers_list"))
	                             ->getItemIndex(
	                                 static_cast<CEGUI::ItemListbox *>(
	                                     m_gui.getRoot()->getChild(
	                                         "servers_list"))
	                                     ->getFirstSelectedItem())];
      }
    return true;
  }
}
