#include "client_test_stdafx.hpp"

Config::Config()
    : m_config(), m_connectManagerIp(), m_connectManagerPort(), m_mapConfig(),
      m_mapMD5()
{
  loadConfig("client.ini");
}

Config &Config::getInstance()
{
  static Config instance;
  return (instance);
}

void Config::checkMD5(std::string const &filePath,
                      std::map<std::string, std::string> &md5)
{
  crypto::Hash<crypto::AHash::MD5> crypt;
  DIR *                            dir;
  struct dirent *                  ent;

  nope::log::Log(Debug) << "Opening " + filePath;
  dir = opendir(filePath.c_str());
  if (!dir)
    {
      // TODO do correct one
      nope::log::Log(Error) << "Cannot open " + filePath;
      throw std::exception();
    }

  // Loop over each file
  while ((ent = readdir(dir)))
    {
      std::ifstream     fileReader;
      std::stringstream buffer;
      std::string       finalBuff;
      std::string       md5Hash;

      if (ent->d_name[0] == '.')
	continue;
      std::string fileName = filePath + ent->d_name;
      nope::log::Log(Debug) << "Found " + fileName;
      fileReader.open(fileName.c_str());
      if (!fileReader.good())
	{
	  throw std::exception();
	}
      buffer << fileReader.rdbuf();
      finalBuff = buffer.str();
      crypt.compute(reinterpret_cast<std::uint8_t const *>(finalBuff.c_str()),
                    finalBuff.length());
      md5Hash = crypt.getHash();
      nope::log::Log(Debug) << "File: " << ent->d_name << ", MD5: " << md5Hash;
      fileReader.close();
      md5[ent->d_name] = md5Hash;
    }
  closedir(dir);
}

void Config::loadConfig(std::string const &file)
{
  m_config.loadFrom(file);

  // Load network configuration
  nope::log::Log(Info) << "Loading network configuration";
  m_connectManagerIp = m_config["Network"]["address"];
  m_connectManagerPort =
      static_cast<std::uint16_t>(std::stoi(m_config["Network"]["port"]));

  // Load game server configuration
  nope::log::Log(Info) << "Loading game configuration";
  updateMD5();
}

// Update MD5
void Config::updateMD5()
{
  DIR *          dir;
  struct dirent *ent;
  dir = opendir("./maps/");
  if (!dir)
    {
      // TODO do correct one
      throw std::exception();
    }
  // Loop over each file
  while ((ent = readdir(dir)))
    {
      if (ent->d_name[0] == '.')
	continue;
      std::string fileName = std::string(ent->d_name);
      MapConfig   tmp;

      nope::log::Log(Debug) << "Found " + fileName;
      tmp.name = fileName;
      checkMD5("./maps/" + tmp.name + "/", tmp.md5);
      std::string                      payload;
      crypto::Hash<crypto::AHash::MD5> crypt;
      for (std::pair<std::string const, std::string> cur : tmp.md5)
	{
	  payload += cur.second;
	}
      crypt.compute(reinterpret_cast<std::uint8_t const *>(payload.c_str()),
                    payload.length());
      tmp.md5Str = crypt.getHash();
      nope::log::Log(Debug) << nope::serialization::to_json(tmp);
      m_mapConfig.push_back(std::move(tmp));
    }
  closedir(dir);

  // Get general MD5
  crypto::Hash<crypto::AHash::MD5> crypt;
  std::string                      payload;
  for (MapConfig const &map : m_mapConfig)
    {
      payload += map.md5Str;
    }
  crypt.compute(reinterpret_cast<std::uint8_t const *>(payload.c_str()),
                payload.length());
  m_mapMD5 = crypt.getHash();
  nope::log::Log(Debug) << "Generated global MD5 : " << m_mapMD5;
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

std::vector<MapConfig> const &Config::getMapConfig() const
{
  return (m_mapConfig);
}

std::string const &Config::getMapMD5() const
{
  return (m_mapMD5);
}
