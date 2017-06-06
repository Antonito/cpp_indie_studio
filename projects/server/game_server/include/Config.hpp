#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include "Ini.hpp"

class Config
{
public:
  enum GameMode
  {
    CLASSIC
  };

  static Config &getInstance();

  Config(Config const &) = delete;
  void operator=(Config const &) = delete;

  // Network
  std::string const &getConnectManagerIp() const;
  std::uint16_t      getConnectManagerPort() const;
  std::uint16_t      getGameServerPort() const;
  std::int32_t       getGameServerMaxClients() const;

private:
  Config();
  void loadConfig(std::string const &file);

  // Ini configuration
  ini::Ini m_config;

  // Network
  std::string   m_connectManagerIp;
  std::uint16_t m_connectManagerPort;
  std::uint16_t m_gameServerPort;
  std::int32_t  m_gameServerMaxClients;

  // Game
};

#endif // !CONFIG_HPP_
