//
// Created by duhieu_b on 14/06/17.
//

#include "pakpak_stdafx.hpp"

namespace core
{
  SaveData::SaveData() : m_key(""), m_data(), m_xor(42), m_crypto()
  {
  }

  SaveData::~SaveData()
  {
  }

  SaveData::SaveData(SaveData const &cpy)
      : m_key(cpy.m_key), m_data(cpy.m_data), m_xor(cpy.m_xor), m_crypto()
  {
  }

  void SaveData::generate()
  {
    nope::log::Log(Debug) << "Generating key sav data";

    m_crypto.compute(reinterpret_cast<std::uint8_t const *>(&m_data),
                     sizeof(m_data));
    m_key = m_crypto.getHash();
    nope::log::Log(Debug) << "Generate key : " << m_key;
  }

  void SaveData::setData(Data &that)
  {
    m_data = that;
  }

  void SaveData::saveInFile(std::string const &file)
  {
    if (isKeyGenerate())
      {
	std::ofstream ofs;

	ofs.open(file, std::ios::trunc);
	if (ofs.is_open())
	  {
	    nope::log::Log(Debug) << "Key save in File : " << m_key;
	    ofs.write(toXor(m_key).c_str(),
	              static_cast<std::streamsize>(m_key.length()));
            nope::log::Log(Debug) << "Key with xor : " << toXor(m_key);
	    nope::log::Log(Debug)
	        << "Save in file => Struct : \nBest Time : " << m_data.s_bestTime
	        << "\nMax Speed : " << m_data.s_maxSpeed
	        << "\nTrackFinished : " << m_data.s_trackFinished
                << "\nTotal Km : " << m_data.s_totalKm
                << "\nCollision count : " << m_data.s_collisionCount;
	    char *structToXor =
	        toXor(reinterpret_cast<char *>(&m_data), sizeof(m_data));
	    ofs.write(structToXor, sizeof(m_data));
	    delete[] structToXor;
	  }
	else
	  {
	    nope::log::Log(Error) << "**Warning cannot save in " << file
	                          << "**";
	  }
	ofs.close();
      }
  }

  bool SaveData::isKeyGenerate() const
  {
    return (m_key != "");
  }

  Data &SaveData::getData()
  {
    return m_data;
  }

  bool SaveData::compareKey(std::string const &key)
  {
    return (key == m_key);
  }

  void SaveData::recupDataFromFile(std::string const &file)
  {
    std::ifstream ifs;
    std::string   key;
    std::string   buf;

    ifs.open(file, std::ios::binary);
    if (ifs.is_open())
      {
	std::stringstream ss;
	ss << ifs.rdbuf();

	key = ss.str().substr(0, 32);
	buf = ss.str().substr(32);
	key = toXor(key);
	char *xorToStruct = toXor(buf.c_str(), sizeof(m_data));
	nope::log::Log(Debug) << "Recup from file " << file
	                      << " Key : " << key;
	std::memcpy(reinterpret_cast<char *>(&m_data), xorToStruct,
	            sizeof(m_data));
	delete[] xorToStruct;
	ifs.close();
	nope::log::Log(Debug)
	        << "Recup form file => Struct : \nBest Time : " << m_data.s_bestTime
	        << "\nMax Speed : " << m_data.s_maxSpeed
	        << "\nTrackFinished : " << m_data.s_trackFinished
                << "\nTotal Km : " << m_data.s_totalKm
                << "\nCollision count : " << m_data.s_collisionCount;
	generate();
	nope::log::Log(Debug) << "END GENERATE KEY";

	if (!compareKey(key))
	  {
	    nope::log::Log(Debug) << "File Corrupt, reset data file";
	    m_data.reset();
	    saveInFile(file);
	  }
      }
    else
      {
	saveInFile(file);
      }
  }

  std::string SaveData::toXor(std::string const &elem)
  {
    std::string xorStr(elem);
    for (char &c : xorStr)
      {
	c ^= static_cast<char>(m_xor);
      }
    return xorStr;
  }

  char *SaveData::toXor(char const *elem, std::size_t const length)
  {
    char *xorStr = new char[length];

    std::memcpy(xorStr, elem, length);
    for (std::size_t i = 0; i < length; ++i)
      {
	xorStr[i] ^= static_cast<char>(m_xor);
      }
    return xorStr;
  }
}
