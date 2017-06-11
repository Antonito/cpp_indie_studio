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

void Config::checkMD5(std::string const &filePath, std::map<std::string, std::string> &md5)
{
  /*crypto::Hash<crypto::AHash::MD5> crypt;
  bool = crypt.compute(reinterpret_cast<std::uint8_t const *>(c_str), lenBuff);
  std::string md5String = crypt.getHash();*/
  crypto::Hash<crypto::AHash::MD5> crypt;
  std::string basePath = filePath;
  DIR *dir;
  struct dirent *ent;

  dir = opendir(filePath.c_str());
  if (!dir)
  {
    //TODO do correct one
    throw std::exception();
  }
  while ((ent = readdir(dir)))
  {
    std::ifstream fileReader;
    std::stringstream buffer;
    std::string finalBuff;
    std::string md5Hash;

    if (ent->d_name[0] == '.')
      continue;
    std::string fileName = filePath + ent->d_name;
    fileReader.open(fileName.c_str());
    if (!fileReader.good())
    {
      std::cout << "!" << fileName << "!" << std::endl;
      throw std::exception();
    }
    buffer << fileReader.rdbuf();
    finalBuff = buffer.str();
    crypt.compute(reinterpret_cast<std::uint8_t const *>(finalBuff.c_str()), finalBuff.length());
    md5Hash = crypt.getHash();
    nope::log::Log(Debug) << "File: " << ent->d_name << ", MD5: " << md5Hash;
    fileReader.close();
    md5[ent->d_name] = md5Hash;
  }
  closedir(dir);
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
        std::cout << "NAME: " << tmp.name << std::endl;
        tmp.directory = (*it)["directory"];
        checkMD5(tmp.directory, tmp.md5);
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
