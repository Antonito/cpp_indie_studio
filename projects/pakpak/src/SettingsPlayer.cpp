#include "pakpak_stdafx.hpp"

namespace core
{
  static std::map<int, std::string const> playerFile = {
      {0, "player0_settings"},
      {1, "player1_settings"},
      {2, "player2_settings"},
      {3, "player3_settings"},
  };

  SettingsPlayer::SettingsPlayer()
      : m_players(), m_keycodes(), m_used(), m_loaded()
  {
    m_players.resize(5);
    m_keycodes.resize(5);
    m_used.resize(256);
    for (int i = 0; i < 4; ++i)
      {
	m_loaded.push_back(false);
      }
  }

  SettingsPlayer::SettingsPlayer(SettingsPlayer const &that)
      : m_players(that.m_players), m_keycodes(that.m_keycodes),
        m_used(that.m_used), m_loaded(that.m_loaded)
  {
  }

  SettingsPlayer::~SettingsPlayer()
  {
  }

  void SettingsPlayer::loadFromFile(int playerIndex)
  {
    Log(nope::log::Debug) << "SettingsPlayer::LoadFromFile -> " << playerIndex
                          << " : " << playerFile[playerIndex];
    std::stringstream ss;

    if (m_loaded[playerIndex])
      {
	return;
      }
    else
      {
	m_loaded[playerIndex] = true;
      }
    std::ifstream fs(playerFile[playerIndex].c_str());

    if (fs.is_open() == false)
      {
	Log(nope::log::Error) << "Can't open the file";
	throw std::exception();
      }
    ss << fs.rdbuf();
    std::string content = ss.str();

    std::cout << "Index " << playerIndex << ' ' << m_players.size()
              << std::endl;
    m_players[playerIndex] =
        nope::serialization::from_json<SettingsPlayer::GameSettings>(content);
    if (check_used(playerIndex))
      {
	Log(nope::log::Error) << "Config File : key already used";
	throw std::exception();
      }

    setUsed(playerIndex, true);
    fillKey(playerIndex);
    fs.close();
  }

  void SettingsPlayer::fillKey(int playerIndex)
  {
    m_keycodes[playerIndex][m_players[playerIndex].key.speedUp] = "speedUp";
    m_keycodes[playerIndex][m_players[playerIndex].key.slowDown] = "slowDown";
    m_keycodes[playerIndex][m_players[playerIndex].key.turnLeft] = "turnLeft";
    m_keycodes[playerIndex][m_players[playerIndex].key.turnRight] =
        "turnRight";
    m_keycodes[playerIndex][m_players[playerIndex].key.useObject] =
        "useObject";
    m_keycodes[playerIndex][m_players[playerIndex].key.changeView] =
        "changeView";
    m_keycodes[playerIndex][m_players[playerIndex].key.displayMap] =
        "displayMap";
    m_keycodes[playerIndex][m_players[playerIndex].key.openChat] = "openChat";
    m_keycodes[playerIndex][m_players[playerIndex].key.openMenu] = "openMenu";
  }

  void SettingsPlayer::setUsed(int playerIndex, bool used)
  {
    m_used[m_players[playerIndex].key.speedUp] = used;
    m_used[m_players[playerIndex].key.slowDown] = used;
    m_used[m_players[playerIndex].key.turnLeft] = used;
    m_used[m_players[playerIndex].key.turnRight] = used;
    m_used[m_players[playerIndex].key.useObject] = used;
    m_used[m_players[playerIndex].key.changeView] = used;
    m_used[m_players[playerIndex].key.displayMap] = used;
    m_used[m_players[playerIndex].key.openChat] = used;
    m_used[m_players[playerIndex].key.openMenu] = used;
  }

  void SettingsPlayer::unload(int playerIndex)
  {
    Log(nope::log::Debug) << "SettingsPlayer::unload -> " << playerIndex
                          << " : " << playerFile[playerIndex];
    // save(playerIndex);
    setUsed(playerIndex, false);
    m_players.erase(m_players.begin() + playerIndex);
    m_players.resize(5);
  }

  void SettingsPlayer::save(int playerIndex) const
  {
    Log(nope::log::Debug) << "SettingsPlayer::save -> " << playerIndex << " : "
                          << playerFile[playerIndex];
    std::stringstream ss;
    std::ofstream     fs(playerFile[playerIndex].c_str(),
                     std::ofstream::out | std::ofstream::trunc);

    if (fs.is_open() == false)
      {
	throw std::exception();
      }
    fs << nope::serialization::to_json(m_players[playerIndex]);
    fs.close();
  }

  bool SettingsPlayer::check_used(int playerIndex) const
  {
    if (m_used[m_players[playerIndex].key.speedUp] == true ||
        m_used[m_players[playerIndex].key.slowDown] == true ||
        m_used[m_players[playerIndex].key.turnLeft] == true ||
        m_used[m_players[playerIndex].key.turnRight] == true ||
        m_used[m_players[playerIndex].key.useObject] == true ||
        m_used[m_players[playerIndex].key.changeView] == true ||
        m_used[m_players[playerIndex].key.displayMap] == true ||
        m_used[m_players[playerIndex].key.openChat] == true ||
        m_used[m_players[playerIndex].key.openMenu] == true)
      {
	return true;
      }
    return false;
  }

  std::string const SettingsPlayer::actionForKey(int          playerIndex,
                                                 OIS::KeyCode keyCode) const
  {
    if (m_keycodes[playerIndex].find(keyCode) == m_keycodes[playerIndex].end())
      {
	return ("NO_ACTION");
      }
    return (m_keycodes[playerIndex].at(keyCode));
  }

  SettingsPlayer::GameSettings::Graphic &
      SettingsPlayer::graphics(int playerIndex)
  {
    return (m_players[playerIndex].graphic);
  }

  bool SettingsPlayer::updateKey(int playerIndex, OIS::KeyCode old,
                                 OIS::KeyCode newKey)
  {
    Log(nope::log::Debug) << "SettingsPlayer::updateKey -> "
                          << "oldKey = " << old << " : "
                          << "newKey = " << newKey;
    if (old == newKey)
      return true;
    else if (m_used[newKey])
      return false;
    m_used[old] = false;
    m_used[newKey] = true;
    std::string action = m_keycodes[playerIndex][old];
    m_keycodes[playerIndex].erase(old);
    m_keycodes[playerIndex][newKey] = action;
    return true;
  }

  SettingsPlayer::GameSettings::GameSettings() : key(), graphic()
  {
  }

  SettingsPlayer::GameSettings::GameSettings(GameSettings const &that)
      : key(that.key), graphic(that.graphic)
  {
  }

  SettingsPlayer::GameSettings::GameSettings(GameSettings &&that)
      : key(std::move(that.key)), graphic(std::move(that.graphic))
  {
  }

  SettingsPlayer::GameSettings &SettingsPlayer::GameSettings::
      operator=(GameSettings const &that)
  {
    this->key = that.key;
    this->graphic = that.graphic;
    return (*this);
  }

  SettingsPlayer::GameSettings &SettingsPlayer::GameSettings::
      operator=(GameSettings &&that)
  {
    this->key = std::move(that.key);
    this->graphic = std::move(that.graphic);
    return (*this);
  }

  SettingsPlayer::GameSettings::Key &SettingsPlayer::GameSettings::Key::
      operator=(GameSettings::Key const &that)
  {
    this->speedUp = that.speedUp;
    this->slowDown = that.slowDown;
    this->turnLeft = that.turnLeft;
    this->turnRight = that.turnRight;
    this->useObject = that.useObject;
    this->changeView = that.changeView;
    this->displayMap = that.displayMap;
    this->openChat = that.openChat;
    this->openMenu = that.openMenu;
    return (*this);
  }

  SettingsPlayer::GameSettings::Key &SettingsPlayer::GameSettings::Key::
      operator=(GameSettings::Key &&that)
  {
    this->speedUp = that.speedUp;
    this->slowDown = that.slowDown;
    this->turnLeft = that.turnLeft;
    this->turnRight = that.turnRight;
    this->useObject = that.useObject;
    this->changeView = that.changeView;
    this->displayMap = that.displayMap;
    this->openChat = that.openChat;
    this->openMenu = that.openMenu;
    return (*this);
  }

  SettingsPlayer::GameSettings::Key::Key(Key const &that)
      : speedUp(that.speedUp), slowDown(that.slowDown),
        turnLeft(that.turnLeft), turnRight(that.turnRight),
        useObject(that.useObject), changeView(that.changeView),
        displayMap(that.displayMap), openChat(that.openChat),
        openMenu(that.openMenu)
  {
  }

  SettingsPlayer::GameSettings::Key::Key(Key &&that)
      : speedUp(that.speedUp), slowDown(that.slowDown),
        turnLeft(that.turnLeft), turnRight(that.turnRight),
        useObject(that.useObject), changeView(that.changeView),
        displayMap(that.displayMap), openChat(that.openChat),
        openMenu(that.openMenu)
  {
  }

  SettingsPlayer::GameSettings::Graphic &
      SettingsPlayer::GameSettings::Graphic::
          operator=(GameSettings::Graphic const &that)
  {
    this->sensibility = that.sensibility;
    this->fov = that.fov;
    return (*this);
  }

  SettingsPlayer::GameSettings::Graphic &
      SettingsPlayer::GameSettings::Graphic::
          operator=(GameSettings::Graphic &&that)
  {
    this->sensibility = that.sensibility;
    this->fov = that.fov;
    return (*this);
  }

  SettingsPlayer::GameSettings::Graphic::Graphic(Graphic const &that)
      : sensibility(that.sensibility), fov(that.fov)
  {
  }

  SettingsPlayer::GameSettings::Graphic::Graphic(Graphic &&that)
      : sensibility(that.sensibility), fov(that.fov)
  {
  }

  SettingsPlayer::GameSettings::Key::Key()
      : speedUp(OIS::KeyCode::KC_UP), slowDown(OIS::KeyCode::KC_DOWN),
        turnLeft(OIS::KeyCode::KC_LEFT), turnRight(OIS::KeyCode::KC_RIGHT),
        useObject(OIS::KeyCode::KC_T), changeView(OIS::KeyCode::KC_V),
        displayMap(OIS::KeyCode::KC_M), openChat(OIS::KeyCode::KC_C),
        openMenu(OIS::KeyCode::KC_ESCAPE)
  {
  }

  SettingsPlayer::GameSettings::Graphic::Graphic() : sensibility(5), fov(1.0)
  {
  }
}