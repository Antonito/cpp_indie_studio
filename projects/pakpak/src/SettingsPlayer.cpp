#include "pakpak_stdafx.hpp"

namespace core
{
  static std::map<int, std::string const> playerFile = {
      {0, "settings/player0_settings"},
      {1, "settings/player1_settings"},
      {2, "settings/player2_settings"},
      {3, "settings/player3_settings"},
  };

  static std::map<int, std::string const> scoreFile = {
      {0, "settings/player0_scores"},
      {1, "settings/player1_scores"},
      {2, "settings/player2_scores"},
      {3, "settings/player3_scores"},
  };
  static std::map<OIS::KeyCode, std::string const> textForKey = {
      {OIS::KeyCode::KC_ESCAPE, "ESC"},
      {OIS::KeyCode::KC_1, "1"},
      {OIS::KeyCode::KC_2, "2"},
      {OIS::KeyCode::KC_3, "3"},
      {OIS::KeyCode::KC_4, "4"},
      {OIS::KeyCode::KC_5, "5"},
      {OIS::KeyCode::KC_6, "6"},
      {OIS::KeyCode::KC_7, "7"},
      {OIS::KeyCode::KC_8, "8"},
      {OIS::KeyCode::KC_9, "9"},
      {OIS::KeyCode::KC_0, "0"},
      {OIS::KeyCode::KC_MINUS, "<"}, // - on main keyboard
      {OIS::KeyCode::KC_EQUALS, "="},
      {OIS::KeyCode::KC_BACK, "<-"}, // backspace
      {OIS::KeyCode::KC_TAB, "TAB"},
      {OIS::KeyCode::KC_Q, "Q"},
      {OIS::KeyCode::KC_W, "W"},
      {OIS::KeyCode::KC_E, "E"},
      {OIS::KeyCode::KC_R, "R"},
      {OIS::KeyCode::KC_T, "T"},
      {OIS::KeyCode::KC_Y, "Y"},
      {OIS::KeyCode::KC_U, "U"},
      {OIS::KeyCode::KC_I, "I"},
      {OIS::KeyCode::KC_O, "O"},
      {OIS::KeyCode::KC_P, "P"},
      {OIS::KeyCode::KC_LBRACKET, "{"},
      {OIS::KeyCode::KC_RBRACKET, "}"},
      {OIS::KeyCode::KC_RETURN, "RET"}, // Enter on main keyboard
      {OIS::KeyCode::KC_LCONTROL, "CTRL"},
      {OIS::KeyCode::KC_A, "A"},
      {OIS::KeyCode::KC_S, "S"},
      {OIS::KeyCode::KC_D, "D"},
      {OIS::KeyCode::KC_F, "F"},
      {OIS::KeyCode::KC_G, "G"},
      {OIS::KeyCode::KC_H, "H"},
      {OIS::KeyCode::KC_J, "J"},
      {OIS::KeyCode::KC_K, "K"},
      {OIS::KeyCode::KC_L, "L"},
      {OIS::KeyCode::KC_SEMICOLON, "SCOL"},
      {OIS::KeyCode::KC_APOSTROPHE, "'"},
      {OIS::KeyCode::KC_GRAVE, "GRA"}, // accent
      {OIS::KeyCode::KC_LSHIFT, "LSHIFT"},
      {OIS::KeyCode::KC_BACKSLASH, "\\"},
      {OIS::KeyCode::KC_Z, "Z"},
      {OIS::KeyCode::KC_X, "X"},
      {OIS::KeyCode::KC_C, "C"},
      {OIS::KeyCode::KC_V, "V"},
      {OIS::KeyCode::KC_B, "B"},
      {OIS::KeyCode::KC_N, "N"},
      {OIS::KeyCode::KC_M, "M"},
      {OIS::KeyCode::KC_COMMA, ","},
      {OIS::KeyCode::KC_PERIOD, "PER"}, // . on main keyboard
      {OIS::KeyCode::KC_SLASH, "/"},    // / on main keyboard
      {OIS::KeyCode::KC_RSHIFT, ">"},
      {OIS::KeyCode::KC_MULTIPLY, "*"}, // * on numeric keypad
      {OIS::KeyCode::KC_LMENU, "LMEN"}, // left Alt
      {OIS::KeyCode::KC_SPACE, "SPACE"},
      {OIS::KeyCode::KC_CAPITAL, "CAP"},
      {OIS::KeyCode::KC_F1, "F1"},
      {OIS::KeyCode::KC_F2, "F2"},
      {OIS::KeyCode::KC_F3, "F3"},
      {OIS::KeyCode::KC_F4, "F4"},
      {OIS::KeyCode::KC_F5, "F5"},
      {OIS::KeyCode::KC_F6, "F6"},
      {OIS::KeyCode::KC_F7, "F7"},
      {OIS::KeyCode::KC_F8, "F8"},
      {OIS::KeyCode::KC_F9, "F9"},
      {OIS::KeyCode::KC_F10, "F10"},
      {OIS::KeyCode::KC_NUMLOCK, "NUM"},
      {OIS::KeyCode::KC_SCROLL, "SCROLL"}, // Scroll Lock
      {OIS::KeyCode::KC_NUMPAD7, "PAD7"},
      {OIS::KeyCode::KC_NUMPAD8, "PAD8"},
      {OIS::KeyCode::KC_NUMPAD9, "PAD9"},
      {OIS::KeyCode::KC_SUBTRACT, "-"}, // - on numeric keypad
      {OIS::KeyCode::KC_NUMPAD4, "PAD4"},
      {OIS::KeyCode::KC_NUMPAD5, "PAD5"},
      {OIS::KeyCode::KC_NUMPAD6, "PAD6"},
      {OIS::KeyCode::KC_ADD, "ADD"}, // + on numeric keypad
      {OIS::KeyCode::KC_NUMPAD1, "PAD1"},
      {OIS::KeyCode::KC_NUMPAD2, "PAD2"},
      {OIS::KeyCode::KC_NUMPAD3, "PAD3"},
      {OIS::KeyCode::KC_NUMPAD0, "PAD0"},
      {OIS::KeyCode::KC_DECIMAL, "DEC"}, // . on numeric keypad
      {OIS::KeyCode::KC_OEM_102, "OEM"}, // < > | on UK/Germany keyboards
      {OIS::KeyCode::KC_F11, "F11"},
      {OIS::KeyCode::KC_F12, "F12"},
      {OIS::KeyCode::KC_F13, "F13"},   //                     (NEC PC98)
      {OIS::KeyCode::KC_F14, "F14"},   //                     (NEC PC98)
      {OIS::KeyCode::KC_F15, "F15"},   //                     (NEC PC98)
      {OIS::KeyCode::KC_KANA, "KANA"}, // (Japanese keyboard)
      {OIS::KeyCode::KC_ABNT_C1,
       "ABNT"}, // / ? on Portugese (Brazilian) keyboards
      {OIS::KeyCode::KC_CONVERT, "CONV"},    // (Japanese keyboard)
      {OIS::KeyCode::KC_NOCONVERT, "NCONV"}, // (Japanese keyboard)
      {OIS::KeyCode::KC_YEN, "YEN"},         // (Japanese keyboard)
      {OIS::KeyCode::KC_ABNT_C2,
       "ABNT"}, // Numpad . on Portugese (Brazilian) keyboards
      {OIS::KeyCode::KC_NUMPADEQUALS,
       "PAD="}, // , ""}, on numeric keypad (NEC PC98)
      {OIS::KeyCode::KC_PREVTRACK,
       "PREV"}, // Previous Track ({OIS::KeyCode::KC_CIRCUMFLEX on Japanese
                // keyboard)
      {OIS::KeyCode::KC_AT, "AT"},       //                     (NEC PC98)
      {OIS::KeyCode::KC_COLON, "COL"},   //                     (NEC PC98)
      {OIS::KeyCode::KC_UNDERLINE, "_"}, //                     (NEC PC98)
      {OIS::KeyCode::KC_KANJI, "KANJI"}, // (Japanese keyboard)
      {OIS::KeyCode::KC_STOP, "STOP"},   //                     (NEC PC98)
      {OIS::KeyCode::KC_AX, "AX"},       //                     (Japan AX)
      {OIS::KeyCode::KC_UNLABELED,
       "UNLABLED"},                         //                        (J3100)
      {OIS::KeyCode::KC_NEXTTRACK, "NEXT"}, // Next Track
      {OIS::KeyCode::KC_NUMPADENTER, "PADENTR"}, // Enter on numeric keypad
      {OIS::KeyCode::KC_RCONTROL, "RCTRL"},
      {OIS::KeyCode::KC_MUTE, "MUTE"},       // Mute
      {OIS::KeyCode::KC_CALCULATOR, "CALC"}, // Calculator
      {OIS::KeyCode::KC_PLAYPAUSE, "PAUSE"}, // Play / Pause
      {OIS::KeyCode::KC_MEDIASTOP, "STOP"},  // Media Stop
      {OIS::KeyCode::KC_VOLUMEDOWN, "VOL-"}, // Volume -
      {OIS::KeyCode::KC_VOLUMEUP, "VOL+"},   // Volume +
      {OIS::KeyCode::KC_WEBHOME, "HOME"},    // Web home
      {OIS::KeyCode::KC_NUMPADCOMMA,
       "PADCOMMA"},                     // , on numeric keypad (NEC PC98)
      {OIS::KeyCode::KC_DIVIDE, "DIV"}, // / on numeric keypad
      {OIS::KeyCode::KC_SYSRQ, "SYSRQ"},
      {OIS::KeyCode::KC_RMENU, "RMENU"},         // right Alt
      {OIS::KeyCode::KC_PAUSE, "PAUSE"},         // Pause
      {OIS::KeyCode::KC_HOME, "HOME"},           // Home on arrow keypad
      {OIS::KeyCode::KC_UP, "UP"},               // UpArrow on arrow keypad
      {OIS::KeyCode::KC_PGUP, "PGUP"},           // PgUp on arrow keypad
      {OIS::KeyCode::KC_LEFT, "LEFT"},           // LeftArrow on arrow keypad
      {OIS::KeyCode::KC_RIGHT, "RIGHT"},         // RightArrow on arrow keypad
      {OIS::KeyCode::KC_END, "END"},             // End on arrow keypad
      {OIS::KeyCode::KC_DOWN, "DOWN"},           // DownArrow on arrow keypad
      {OIS::KeyCode::KC_PGDOWN, "PGDOWN"},       // PgDn on arrow keypad
      {OIS::KeyCode::KC_INSERT, "INSERT"},       // Insert on arrow keypad
      {OIS::KeyCode::KC_DELETE, "DEL"},          // Delete on arrow keypad
      {OIS::KeyCode::KC_LWIN, "LWIN"},           // Left Windows key
      {OIS::KeyCode::KC_RWIN, "RWIN"},           // Right Windows key
      {OIS::KeyCode::KC_APPS, "APPS"},           // AppMenu key
      {OIS::KeyCode::KC_POWER, "POWER"},         // System Power
      {OIS::KeyCode::KC_SLEEP, "SLEEP"},         // System Sleep
      {OIS::KeyCode::KC_WAKE, "WAKE"},           // System Wake
      {OIS::KeyCode::KC_WEBSEARCH, "WEBSEARCH"}, // Web Search
      {OIS::KeyCode::KC_WEBFAVORITES, "WEBFAV"}, // Web Favorites
      {OIS::KeyCode::KC_WEBREFRESH, "WEBREFRESH"}, // Web Refresh
      {OIS::KeyCode::KC_WEBSTOP, "WEBSTOP"},       // Web Stop
      {OIS::KeyCode::KC_WEBFORWARD, "WEBFORW"},    // Web Forward
      {OIS::KeyCode::KC_WEBBACK, "WEBBACK"},       // Web Back
      {OIS::KeyCode::KC_MYCOMPUTER, "MYCOMPUTER"}, // My Computer
      {OIS::KeyCode::KC_MAIL, "MAIL"},             // Mail
      {OIS::KeyCode::KC_MEDIASELECT, "MEDIA"},     // Media Select
  };

  SettingsPlayer::SettingsPlayer()
      : m_data(), m_players(), m_keycodes(), m_used(), m_loaded(),
        m_playerCount(1)
  {
    m_players.resize(5);
    m_data.resize(5);
    m_keycodes.resize(5);
    m_used.resize(256);
    for (std::size_t i = 0; i < 4; ++i)
      {
	m_loaded.push_back(false);
	loadFromFile(i);
	m_data[i].generate();
	Log(nope::log::Debug) << "SaveData::recupFile";
	m_data[i].recupDataFromFile(scoreFile[static_cast<int>(i)]);
      }
  }

  SettingsPlayer::SettingsPlayer(SettingsPlayer const &that)
      : m_data(that.m_data), m_players(that.m_players),
        m_keycodes(that.m_keycodes), m_used(that.m_used),
        m_loaded(that.m_loaded), m_playerCount(1)
  {
  }

  SettingsPlayer::~SettingsPlayer()
  {
  }

  void SettingsPlayer::loadFromFile(std::size_t playerIndex)
  {
    Log(nope::log::Debug) << "SettingsPlayer::LoadFromFile -> " << playerIndex
                          << " : "
                          << playerFile[static_cast<int>(playerIndex)];
    std::stringstream ss;

    if (m_loaded[playerIndex])
      {
	return;
      }
    else
      {
	m_loaded[playerIndex] = true;
      }
    std::ifstream fs;

    // This allow to throw in case of fail to open
    fs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fs.open(playerFile[static_cast<int>(playerIndex)].c_str());
    ss << fs.rdbuf();
    std::string content = ss.str();

    nope::log::Log(Debug) << "Index " << playerIndex << ' '
                          << m_players.size();

    m_players[playerIndex] =
        nope::serialization::from_json<SettingsPlayer::GameSettings>(content);
    if (check_used(playerIndex))
      {
	Log(nope::log::Debug) << "Config File : key already used";
	throw IOError("Settings File Error: Key already used");
      }

    setUsed(playerIndex, true);
    fillKey(playerIndex);
    fs.close();
  }

  void SettingsPlayer::fillKey(std::size_t const playerIndex)
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

  void SettingsPlayer::setUsed(std::size_t const playerIndex, bool used)
  {
    m_used[static_cast<std::size_t>(m_players[playerIndex].key.speedUp)] =
        used;
    m_used[static_cast<std::size_t>(m_players[playerIndex].key.slowDown)] =
        used;
    m_used[static_cast<std::size_t>(m_players[playerIndex].key.turnLeft)] =
        used;
    m_used[static_cast<std::size_t>(m_players[playerIndex].key.turnRight)] =
        used;
    m_used[static_cast<std::size_t>(m_players[playerIndex].key.useObject)] =
        used;
    m_used[static_cast<std::size_t>(m_players[playerIndex].key.changeView)] =
        used;
    m_used[static_cast<std::size_t>(m_players[playerIndex].key.displayMap)] =
        used;
    m_used[static_cast<std::size_t>(m_players[playerIndex].key.openChat)] =
        used;
    m_used[static_cast<std::size_t>(m_players[playerIndex].key.openMenu)] =
        used;
  }

  void SettingsPlayer::unload(std::size_t const playerIndex)
  {
    Log(nope::log::Debug) << "SettingsPlayer::unload -> " << playerIndex
                          << " : "
                          << playerFile[static_cast<int>(playerIndex)];
    // save(playerIndex);
    setUsed(playerIndex, false);
    m_players.erase(m_players.begin() +
                    static_cast<CEGUI::String::difference_type>(playerIndex));
    m_players.resize(5);
  }

  void SettingsPlayer::save(std::size_t const playerIndex) const
  {
    Log(nope::log::Debug) << "SettingsPlayer::save -> " << playerIndex << " : "
                          << playerFile[static_cast<int>(playerIndex)];
    std::ofstream fs(playerFile[static_cast<int>(playerIndex)].c_str(),
                     std::ofstream::out | std::ofstream::trunc);

    if (fs.is_open() == false)
      {
	throw IOError("Cannot open " +
	              playerFile[static_cast<int>(playerIndex)]);
      }
    fs << nope::serialization::to_json(m_players[playerIndex]);
    fs.close();
  }

  bool SettingsPlayer::check_used(std::size_t const playerIndex) const
  {
    if (m_used[static_cast<std::size_t const>(
            m_players[playerIndex].key.speedUp)] == true ||
        m_used[static_cast<std::size_t const>(
            m_players[playerIndex].key.slowDown)] == true ||
        m_used[static_cast<std::size_t const>(
            m_players[playerIndex].key.turnLeft)] == true ||
        m_used[static_cast<std::size_t const>(
            m_players[playerIndex].key.turnRight)] == true ||
        m_used[static_cast<std::size_t const>(
            m_players[playerIndex].key.useObject)] == true ||
        m_used[static_cast<std::size_t const>(
            m_players[playerIndex].key.changeView)] == true ||
        m_used[static_cast<std::size_t const>(
            m_players[playerIndex].key.displayMap)] == true ||
        m_used[static_cast<std::size_t const>(
            m_players[playerIndex].key.openChat)] == true ||
        m_used[static_cast<std::size_t const>(
            m_players[playerIndex].key.openMenu)] == true)
      {
	return true;
      }
    return false;
  }

  std::string const SettingsPlayer::getTextForKey(OIS::KeyCode keycode) const
  {
    return (textForKey[keycode]);
  }

  std::string const SettingsPlayer::actionForKey(std::size_t const playerIndex,
                                                 OIS::KeyCode keyCode) const
  {
    if (m_keycodes[playerIndex].find(keyCode) == m_keycodes[playerIndex].end())
      {
	return ("NO_ACTION");
      }
    return (m_keycodes[playerIndex].at(keyCode));
  }

  SettingsPlayer::GameSettings::Graphic &
      SettingsPlayer::graphics(std::size_t const playerIndex)
  {
    return (m_players[playerIndex].graphic);
  }

  bool SettingsPlayer::updateKey(std::size_t const playerIndex,
                                 OIS::KeyCode old, OIS::KeyCode newKey)
  {
    Log(nope::log::Debug) << "SettingsPlayer::updateKey -> "
                          << "oldKey = " << old << " : "
                          << "newKey = " << newKey;
    if (old == newKey)
      return true;
    else if (m_used[newKey])
      {
	std::size_t oldPlayer =
	    static_cast<std::size_t>(switchKey(old, newKey));
	std::string oldAction =
	    m_keycodes[static_cast<std::size_t>(oldPlayer)][newKey];
	std::string newAction =
	    m_keycodes[static_cast<std::size_t>(playerIndex)][old];
	m_keycodes[oldPlayer].erase(newKey);
	m_keycodes[playerIndex].erase(old);
	m_keycodes[oldPlayer][old] = oldAction;
	m_keycodes[playerIndex][newKey] = newAction;
      }
    else
      {
	m_used[old] = false;
	m_used[newKey] = true;
	std::string action = m_keycodes[playerIndex][old];
	m_keycodes[playerIndex].erase(old);
	m_keycodes[playerIndex][newKey] = action;
      }
    return true;
  }

  int SettingsPlayer::switchKey(OIS::KeyCode old, OIS::KeyCode newKey)
  {

    for (std::size_t i = 0; i < 4; ++i)
      {
	if (m_players[i].key.speedUp == newKey)
	  {
	    m_players[i].key.speedUp = old;
	    return (static_cast<int>(i));
	  }
	if (m_players[i].key.slowDown == newKey)
	  {
	    m_players[i].key.slowDown = old;
	    return (static_cast<int>(i));
	  }
	if (m_players[i].key.turnRight == newKey)
	  {
	    m_players[i].key.turnRight = old;
	    return (static_cast<int>(i));
	  }
	if (m_players[i].key.turnLeft == newKey)
	  {
	    m_players[i].key.turnLeft = old;
	    return (static_cast<int>(i));
	  }
	if (m_players[i].key.useObject == newKey)
	  {
	    m_players[i].key.useObject = old;
	    return (static_cast<int>(i));
	  }
	if (m_players[i].key.openMenu == newKey)
	  {
	    m_players[i].key.openMenu = old;
	    return (static_cast<int>(i));
	  }
      }
    return (0);
  }

  SettingsPlayer::GameSettings &
      SettingsPlayer::getPlayer(std::size_t const playerIndex)
  {
    return (m_players[playerIndex]);
  }

  std::uint32_t SettingsPlayer::getPlayerCount() const
  {
    return m_playerCount;
  }

  void SettingsPlayer::setPlayerCount(std::uint32_t playerCount)
  {
    m_playerCount = playerCount;
  }

  std::vector<SaveData> &SettingsPlayer::getSaveData()
  {
    return (m_data);
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
