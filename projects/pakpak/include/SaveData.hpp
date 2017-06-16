//
// Created by duhieu_b on 14/06/17.
//

#ifndef CPP_INDIE_STUDIO_SaveData_HPP
#define CPP_INDIE_STUDIO_SaveData_HPP

#include <iostream>
#include "AHash.hpp"
#include "Hash.hpp"
#include "Data.hpp"

class SaveData
{
public:
  SaveData();
  ~SaveData();
  SaveData(SaveData const &);
  SaveData &operator=(SaveData &);
  SaveData(SaveData &&) = delete;

  void generate();

  void setData(Data &);

  std::string toXor(std::string const &);

  char *toXor(char const *elem, std::size_t const length);

  void saveInFile(std::string const &);

  void recupDataFromFile(std::string const &);

  bool compareKey(std::string const &);

  bool isKeyGenerate() const;

  Data &getData();

private:
  std::string                      m_key;
  Data                             m_data;
  std::int32_t                     m_xor;
  crypto::Hash<crypto::AHash::MD5> m_crypto;
};

#endif // CPP_INDIE_STUDIO_SaveData_HPP
