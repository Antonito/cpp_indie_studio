#ifndef SETTINGSPLAYER_HPP_
#define SETTINGSPLAYER_HPP_

#include <string>
#if defined __APPLE__
#include <ois/OIS.h>
#else
#include <OIS/OIS.h>
#endif
#include "Metadata.hpp"
#include "SaveData.hpp"

// Disable clang warning for templated class padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

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

    void loadFromFile(std::size_t playerIndex);
    void unload(std::size_t const playerIndex);
    void save(std::size_t const playerIndex) const;

    bool check_used(std::size_t const playerIndex) const;
    std::string const getTextForKey(OIS::KeyCode keycode) const;
    std::string const actionForKey(std::size_t const playerIndex,
                                   OIS::KeyCode      keyCode) const;
    GameSettings::Graphic &graphics(std::size_t const playerIndex);

    bool updateKey(std::size_t const playerIndex, OIS::KeyCode old,
                   OIS::KeyCode newKey);
    void fillKey(std::size_t const playerIndex);
    void setUsed(std::size_t const playerIndex, bool used);
    int switchKey(OIS::KeyCode old, OIS::KeyCode newKey);

    GameSettings &getPlayer(std::size_t const playerIndex);
    std::uint32_t getPlayerCount() const;
    void setPlayerCount(std::uint32_t playerCount);

    std::vector<SaveData> m_data;

  private:
    std::vector<GameSettings> m_players;
    std::vector<std::map<std::int32_t, std::string>> m_keycodes;
    std::vector<bool> m_used;
    std::vector<bool> m_loaded;
    std::uint32_t     m_playerCount;
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !SETTINGSPLAYER_HPP_
