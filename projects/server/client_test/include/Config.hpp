#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include "ConfigTools.hpp"
#include "Ini.hpp"

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

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
  std::string const &           getConnectManagerIp() const;
  std::uint16_t                 getConnectManagerPort() const;
  std::vector<MapConfig> const &getMapConfig() const;
  std::string const &           getMapMD5() const;
  void                          updateMD5();

private:
  Config();
  void loadConfig(std::string const &file);
  void checkMD5(std::string const &filePath,
                std::map<std::string, std::string> &md5);

  // Ini configuration
  ini::Ini m_config;

  // Network
  std::string            m_connectManagerIp;
  std::uint16_t          m_connectManagerPort;
  std::vector<MapConfig> m_mapConfig;
  std::string            m_mapMD5;

  // Game
};

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !CONFIG_HPP_
