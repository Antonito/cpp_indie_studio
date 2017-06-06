#include "game_server_stdafx.hpp"

Config::Config()
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
  m_config.loadFrom(file);

  // Load network configuration
  m_connectManagerIp = m_config["Network"]["connectManagerIp"];
  m_connectManagerPort = static_cast<std::uint16_t>(
      std::stoi(m_config["Network"]["connectManagerPort"]));
  m_gameServerPort = static_cast<std::uint16_t>(
      std::stoi(m_config["Network"]["gameServerPort"]));
  m_gameServerMaxClients = static_cast<std::uint16_t>(
      std::stoi(m_config["Network"]["maxNumberClients"]));

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
