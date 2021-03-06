#include "pakpak_stdafx.hpp"

namespace game
{
  ContextGame::ContextGame(Ogre::RenderWindow *win, core::InputListener *input,
                           core::SettingsPlayer &settings,
                           core::NetworkManager &net,
                           core::SoundManager &  sound)
      : core::AContext(win, input), m_game(), m_players(), m_ia(),
        m_settings(settings), m_quit(false), m_hud(nullptr), m_net(net),
        m_sound(sound), m_timer(850), m_iaTimer(4850), m_gameStart(false),
        m_networkPacket()
  {
  }

  ContextGame::~ContextGame()
  {
  }

  static const std::vector<std::string> gl_maps = {"test", "test2", "test2",
                                                   "test"};

  void ContextGame::enable()
  {
    nope::log::Log(Debug) << "Game context enabled";

    Pauser::unpause();
    m_input->setMouseEventCallback(this);
    m_input->setKeyboardEventCallback(this);
    m_quit = false;

    nope::log::Log(Debug) << "Creating HUD";
    m_hud = std::make_unique<core::HUD>();

    m_game.resetPhysicWorld();
    m_game.setMap(gl_maps[m_settings.getSelectedMap()]);

    std::size_t nbPlayer = (m_net.isConnected()) ? 1 : 4;
    m_game.setPlayerNb(0);
    m_game.setPlayerNb(nbPlayer);

    std::uint32_t nbLocalPlayer = m_settings.getPlayerCount();
    m_game.setLocalPlayerNb(nbLocalPlayer);
    m_timer.start();
    m_iaTimer.start();

    for (std::size_t i = 0; i < nbPlayer; ++i)
      {
	m_game[i].setCar(std::make_unique<EmptyCar>(
	    m_game, Ogre::Vector3(0, 10, -100.0f * static_cast<float>(i)),
	    Ogre::Quaternion(Ogre::Degree(180), Ogre::Vector3::UNIT_Y)));
      }
    m_game[0].setId((m_net.isConnected()) ? m_net.getId() : 0);

    for (std::size_t i = 0; i < nbLocalPlayer; ++i)
      {
	m_players.emplace_back(std::make_unique<LocalPlayer>(
	    m_win, m_game, m_game.getPlayers(), i, static_cast<int>(i),
	    m_settings, ((i == 0) ? m_hud.get() : nullptr), *this, m_players,
	    nbLocalPlayer, (i == 0) ? m_net.getId() : i, m_sound,
	    m_net.isConnected()));
      }

    if (!m_net.isConnected())
      {
	// Creating AI if local game
	for (std::size_t i = nbLocalPlayer; i < nbPlayer; ++i)
	  {
	    nope::log::Log(Debug) << "Creating AI ...";
	    m_ia.emplace_back(std::make_unique<Ai>(
	        m_game[i].car(), m_game.map().getCheckPoints(), &m_game[i]));
	  }
      }

    updateViewPort();
    m_input->setPhysicWorld(m_game.physicWorld());

    m_sound.playSound(core::ESound::GAME_SONG);
    m_sound.loopSound(core::ESound::GAME_SONG);
    m_sound.playSound(core::ESound::IDLE_KART_SOUND);
    m_sound.loopSound(core::ESound::IDLE_KART_SOUND);
    m_sound.setVolumeSource(core::ESound::IDLE_KART_SOUND,
                            2.0f * m_sound.getVolume());
    m_sound.setVolumeSource(core::ESound::GAME_SONG,
                            0.2f * m_sound.getVolume());
  }

  void ContextGame::updateViewPort()
  {
    int size = static_cast<int>(m_players.size());

    for (int i = 0; i < size; ++i)
      {
	m_players[static_cast<std::size_t>(i)]->setViewPort(
	    static_cast<Ogre::Real>(
	        static_cast<double>((i % 2) * ((size - 1) / 2)) * 0.5),
	    static_cast<Ogre::Real>(
	        static_cast<double>(
	            (((size - 1) / 2) * i / 2 + (1 - (size - 1) / 2) * i)) *
	        0.5),
	    static_cast<Ogre::Real>(
	        1 -
	        0.5 * static_cast<double>((((size - 1) / 2) * (1 - (i / 2)) +
	                                   (i / 2) * (size / 4)))),
	    static_cast<Ogre::Real>(
	        1 - 0.5 * static_cast<double>((size + 1) / 3)));
      }
  }

  void ContextGame::disable()
  {
    nope::log::Log(Debug) << "Game context disabled";
    m_game.setPlayerNb(0);
    m_players.clear();
    m_ia.clear();
    m_gameStart = false;
    m_sound.stopSound(core::ESound::GAME_SONG);
    m_sound.stopSound(core::ESound::IDLE_KART_SOUND);
    m_sound.stopSound(core::ESound::ACC_KART_SOUND);
    m_sound.stopSound(core::ESound::SHOOTING_STAR);
    m_game.clearPhysicWorld();
    m_input->setPhysicWorld(nullptr);
    nope::log::Log(Debug) << "Disabling game.";
    if (m_net.isConnected())
      {
	nope::log::Log(Debug) << "Game is connected to Game Server.";
	m_net.disconnect();
      }
  }

  core::GameState ContextGame::update()
  {
    static std::chrono::steady_clock::time_point lastTimePck =
        std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point now =
        std::chrono::steady_clock::now();

    if (m_net.isConnected())
      {
	// Process network I/O
	if (std::chrono::duration_cast<std::chrono::milliseconds>(now -
	                                                          lastTimePck)
	        .count() >= 17)
	  {
	    std::vector<GameClientToGSPacketUDP> pck;
	    GameClientToGSPacketUDP              pckContent;

	    // Build packet
	    setUDPPacket(pckContent, *m_players[0]);
	    pck.push_back(pckContent);

	    // Send packet
	    nope::log::Log(Debug) << "Sending UDP packet to UDP thread.";
	    m_net.sendUDPPacket(std::move(pck));
	    lastTimePck = std::chrono::steady_clock::now();

	    // Read packets
	    m_networkPacket = m_net.getUDPPacket();

	    // Processing Packets
	    setPlayersFromUDPPackets();
	    m_networkPacket.clear();
	  }

	// Check timeout
	std::vector<PlayerData> &gameData = m_game.getPlayers();
	for (std::vector<PlayerData>::iterator it = gameData.begin() + 1;
	     it != gameData.end();)
	  {
	    bool deleted = false;

	    if (it->hasTimedOut())
	      {
		nope::log::Log(Debug) << "Client time'd out, removing it";
		gameData.erase(it);
		deleted = true;
		it = gameData.end();
	      }
	    if (!deleted)
	      {
		++it;
	      }
	  }
      }

    // Update saveData
    std::size_t i = 0;
    for (std::unique_ptr<LocalPlayer> &p : m_players)
      {
	double rawSpeed = p->car().speed();

	std::int32_t speed = static_cast<std::int32_t>(
	    (rawSpeed > 0 ? rawSpeed : -rawSpeed) / 50);

	if (speed > m_settings.getSaveData()[i].getData().s_maxSpeed)
	  {
	    m_settings.getSaveData()[i].getData().s_maxSpeed = speed;
	  }
	if (p->getFinished() && !p->getSaved())
	  {
	    p->setSaved(true);
	    m_settings.getSaveData()[i].getData().s_trackFinished++;
	    m_settings.getSaveData()[i].getData().s_totalKm += 3;
	    m_settings.getSaveData()[i].getData().s_collisionCount +=
	        p->car().getTotalCrash();
	  }

	++i;
      }

    // Game process
    m_input->capture();
    m_game.update();
    m_quit = m_hud->getQuit();
    if (m_quit)
      {
	for (std::size_t j = 0; j < m_settings.getSaveData().size(); ++j)
	  {
	    m_settings.getSaveData()[j].generate();
	    m_settings.getSaveData()[j].saveInFile(
	        "settings/player" + std::to_string(j) + "_scores");
	  }
      }
    return (m_quit ? core::GameState::Menu : core::GameState::InGame);
  }

  void ContextGame::display()
  {
    if (!m_net.isConnected())
      {
	if (m_timer.reached() && !m_gameStart)
	  {
	    m_sound.playSound(core::ESound::START_SONG);
	    m_sound.setVolumeSource(core::ESound::START_SONG,
	                            0.4f * m_sound.getVolume());
	    m_gameStart = true;
	  }
      }

    for (std::uint8_t i = 0; i < m_players.size(); ++i)
      {
	m_players[i]->display();
      }

    if (!m_net.isConnected() && m_iaTimer.reached())
      {
	for (std::unique_ptr<Ai> const &l_ia : m_ia)
	  {
	    l_ia->race();
	  }
      }
  }

  bool ContextGame::keyPressed(OIS::KeyEvent const &ke)
  {
    std::size_t i = 0;
    for (std::unique_ptr<LocalPlayer> &p : m_players)
      {
	nope::log::Log(Debug) << "\t\tPressed for player " << i;
	p->keyPressed(ke);
	++i;
      }
    nope::log::Log(Debug) << "\n";
    return (true);
  }

  bool ContextGame::keyReleased(OIS::KeyEvent const &ke)
  {
    for (std::unique_ptr<LocalPlayer> &p : m_players)
      {
	p->keyReleased(ke);
      }
    return (true);
  }

  bool ContextGame::mouseMoved(OIS::MouseEvent const &me)
  {
    for (std::unique_ptr<LocalPlayer> &p : m_players)
      {
	p->mouseMoved(me);
      }
    return (true);
  }

  bool ContextGame::mousePressed(OIS::MouseEvent const &me,
                                 OIS::MouseButtonID     id)
  {
    for (std::unique_ptr<LocalPlayer> &p : m_players)
      {
	p->mousePressed(me, id);
      }
    return (true);
  }

  bool ContextGame::mouseReleased(OIS::MouseEvent const &me,
                                  OIS::MouseButtonID     id)
  {
    for (std::unique_ptr<LocalPlayer> &p : m_players)
      {
	p->mouseReleased(me, id);
      }
    return (true);
  }

  void ContextGame::setQuit(bool quit)
  {
    m_quit = quit;
  }

  void ContextGame::setUDPPacket(GameClientToGSPacketUDP &packet,
                                 LocalPlayer &            player)
  {
    packet.reinit();
    packet.pck.id = player.getID();
    nope::log::Log(Debug) << "================= SENDING ======\nSetting up "
                             "UDP packet for player : "
                          << packet.pck.id;

    game::EmptyCar &car = static_cast<game::EmptyCar &>(player.car());
    setUDPPatcketPosition(packet, car.position());
    setUDPPacketDirection(packet, car.direction());
    nope::log::Log(Debug) << "Speed:\n\t\t\t speed :" << car.speed();
    packet.pck.speed = static_cast<std::uint32_t>(car.speed() * 1000.0);
    nope::log::Log(Debug) << "=====================";
  }

  void ContextGame::setUDPPacketDirection(GameClientToGSPacketUDP &packet,
                                          Ogre::Quaternion const & dir)
  {
    std::vector<float> vec;

    nope::log::Log(Debug) << "Direction :"
                          << "\n\t\t\t x : " << dir.x
                          << "\n\t\t\t y : " << dir.y
                          << "\n\t\t\t z : " << dir.z
                          << "\n\t\t\t w : " << dir.w;
    vec.push_back(dir.x);
    vec.push_back(dir.y);
    vec.push_back(dir.z);
    vec.push_back(dir.w);
    packet.setDirection(vec);
  }

  void ContextGame::setUDPPatcketPosition(GameClientToGSPacketUDP &packet,
                                          Ogre::Vector3 const &    pos)
  {
    std::vector<float> vec;

    nope::log::Log(Debug) << "Position :"
                          << "\n\t\t\t x : " << pos.x
                          << "\n\t\t\t y : " << pos.y
                          << "\n\t\t\t z : " << pos.z;
    vec.push_back(pos.x);
    vec.push_back(pos.y);
    vec.push_back(pos.z);
    packet.setPosition(vec);
  }

  void ContextGame::setPlayersFromUDPPackets()
  {
    nope::log::Log(Debug)
        << "=========WRITTING======\nProcessing server UDP packets";
    for (GameClientToGSPacketUDP &packet : m_networkPacket)
      {
	std::vector<PlayerData> &gameData = m_game.getPlayers();

	std::vector<PlayerData>::iterator player = std::find_if(
	    gameData.begin(), gameData.end(), [&packet](PlayerData &pl) {
	      return (pl.getId() == packet.pck.id);
	    });

	if (player == gameData.end())
	  {
	    // Add new player
	    std::size_t const i = gameData.size();

	    nope::log::Log(Debug)
	        << "Adding player [" << i << "] - Id: " << packet.pck.id;
	    gameData.push_back(PlayerData());
	    gameData.back().setCar(std::make_unique<EmptyCar>(
	        m_game, Ogre::Vector3(0, 10, -100.0f * static_cast<float>(i)),
	        Ogre::Quaternion(Ogre::Degree(180), Ogre::Vector3::UNIT_Y)));
	    gameData.back().setId(packet.pck.id);

	    player = gameData.end() - 1;
	  }

	player->updateLastAction();
	game::EmptyCar &car = static_cast<game::EmptyCar &>(player->car());
	nope::log::Log(Debug) << "====> PlayerID: " << packet.pck.id;

	car.setPacketData(packet, player == gameData.begin());
	nope::log::Log(Debug) << "Speed:\n\t\t\t speed :" << car.speed();
      }
    nope::log::Log(Debug) << "*****************************";
  }
}
