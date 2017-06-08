#include "game_server_stdafx.hpp"

Config::Config()
    : m_config(), m_connectManagerIp(), m_connectManagerPort(),
      m_gameServerPort(), m_gameServerMaxClients()
{
  loadConfig("game_server.ini");
}

Config &Config::getInstance()
{
  static Config instance;
  return (instance);
}

void Config::loadConfig(std::string const &file)
{
  std::string const mapCatDefault = "Track_";
  m_config.loadFrom(file);

  // Load network configuration
  m_connectManagerIp = m_config["Network"]["connectManagerIp"];
  m_connectManagerPort = static_cast<std::uint16_t>(
      std::stoi(m_config["Network"]["connectManagerPort"]));
  m_gameServerPort = static_cast<std::uint16_t>(
      std::stoi(m_config["Network"]["gameServerPort"]));
  m_gameServerMaxClients = static_cast<std::uint16_t>(
      std::stoi(m_config["Network"]["maxNumberClients"]));

  // TODO change condition !
  for (std::vector<ini::Section>::const_iterator it = m_config.cbegin(); it != m_config.cend(); ++it)
    {
      if (it->name().compare(0, mapCatDefault.length(), mapCatDefault) == 0)
      {
        MapConfig   tmp;
        tmp.name = (*it)["name"];
        tmp.directory = (*it)["directory"];
        tmp.gameMode = (*it)["gameMode"];
        tmp.nbLaps = std::stoi((*it)["laps"]);
        nope::log::Log(Debug) << nope::serialization::to_json(tmp);
        m_mapConfig.push_back(std::move(tmp));
      }
    }
  // Load game server configuration
}

// Getters
std::string const &Config::getConnectManagerIp() const
{
  return (m_connectManagerIp);
}

std::uint16_t Config::getConnectManagerPort() const
{
  return (m_connectManagerPort);
}

std::uint16_t Config::getGameServerPort() const
{
  return (m_gameServerPort);
}

std::int32_t Config::getGameServerMaxClients() const
{
  return (m_gameServerMaxClients);
}
