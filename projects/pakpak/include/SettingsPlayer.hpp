#ifndef SETTINGSPLAYER_HPP_
#define SETTINGSPLAYER_HPP_

#include <string>
#include <OIS/OIS.h>
#include "Metadata.hpp"

namespace core
{
  class SettingsPlayer
  {

  public:
    struct GameSettings
    {
      GameSettings();

      GameSettings(GameSettings const &);
      GameSettings(GameSettings &&);
      GameSettings &operator=(GameSettings const &);
      GameSettings &operator=(GameSettings &&);

      struct Key
      {
	Key();
	Key(Key const &);
	Key(Key &&);
	Key &operator=(Key const &);
	Key &operator=(Key &&);

	// clang-format off
      NOPE_SERIAL_MEMBER(
      std::int32_t, speedUp,
      std::int32_t, slowDown,
      std::int32_t, turnLeft,
      std::int32_t, turnRight,
      std::int32_t, useObject,
      std::int32_t, changeView,
      std::int32_t, displayMap,
      std::int32_t, openChat,
      std::int32_t, openMenu)
	// clang-format on
      };

      struct Graphic
      {
	Graphic();
	Graphic(Graphic const &);
	Graphic(Graphic &&);
	Graphic &operator=(Graphic const &);
	Graphic &operator=(Graphic &&);
	// clang-format off
	NOPE_SERIAL_MEMBER(
	std::int32_t, sensibility,
	float, fov)
	// clang-format on
      };

      // clang-format off

      NOPE_SERIAL_MEMBER(
	      Key, key,
	      Graphic, graphic)
      // clang-format on
    };

    SettingsPlayer();
    SettingsPlayer(SettingsPlayer const &);
    SettingsPlayer(SettingsPlayer &&) = delete;
    ~SettingsPlayer();

    SettingsPlayer &operator=(SettingsPlayer const &) = delete;
    SettingsPlayer &operator=(SettingsPlayer &&) = delete;

    void loadFromFile(int playerIndex);
    void unload(int playerIndex);
    void save(int playerIndex) const;

    bool check_used(int playerIndex) const;
    std::string const getTextForKey(OIS::KeyCode keycode) const;
    std::string const actionForKey(int          playerIndex,
                                   OIS::KeyCode keyCode) const;
    GameSettings::Graphic &graphics(int playerIndex);

    bool updateKey(int playerIndex, OIS::KeyCode old, OIS::KeyCode newKey);
    void fillKey(int playerIndex);
    void setUsed(int playerIndex, bool used);

  private:
    std::vector<GameSettings> m_players;
    std::vector<std::map<std::int32_t, std::string>> m_keycodes;
    std::vector<bool> m_used;
    std::vector<bool> m_loaded;
  };
}

#endif // !SETTINGSPLAYER_HPP_
