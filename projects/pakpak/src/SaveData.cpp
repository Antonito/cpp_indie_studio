//
// Created by duhieu_b on 14/06/17.
//

#include <fstream>
#include <IOError.hpp>
#include <cstring>
#include "SaveData.hpp"
#include "Logger.hpp"

namespace core
{
  SaveData::SaveData() : m_key(""), m_data(), m_xor(42), m_crypto()
  {
  }

  SaveData::~SaveData()
  {
  }

  SaveData::SaveData(SaveData const &cpy)
      : m_key(cpy.m_key), m_data(cpy.m_data), m_xor(cpy.m_xor)
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
	    ofs.write(toXor(m_key).c_str(),
	              static_cast<std::streamsize>(m_key.length()));
	    char *structToXor =
	        toXor(reinterpret_cast<char *>(&m_data), sizeof(m_data));
	    ofs.write(structToXor, sizeof(m_data));
	    delete structToXor;
	  }
	else
	  {
	    throw IOError("Failed to open file.");
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
	nope::log::Log(Debug)
	    << "Recup from file : " << file << " Key : " << key;
	std::memcpy(reinterpret_cast<char *>(&m_data), xorToStruct,
	            sizeof(m_data));
	delete xorToStruct;
	ifs.close();
	generate();
	if (!compareKey(key))
	  {
	    throw IOError("File is corrupted");
	  }
      }
    else
      {
	throw IOError("Cannot open file");
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
