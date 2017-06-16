//
// Created by duhieu_b on 14/06/17.
//

#ifndef CPP_INDIE_STUDIO_SaveData_HPP
#define CPP_INDIE_STUDIO_SaveData_HPP

#include <iostream>
#include "AHash.hpp"
#include "Hash.hpp"
#include "Data.hpp"

namespace core
{
  class SaveData
  {
  public:
    SaveData();
    ~SaveData();
    SaveData(SaveData const &);
    SaveData &operator=(SaveData &) = delete;
    SaveData(SaveData &&) = delete;

    void generate();

    void setData(Data &);

    std::string toXor(std::string const &);

    char *toXor(char const *elem, std::int32_t length);

    void saveInFile(std::string const &);

    void recupDataFromFile(std::string const &);

    bool compareKey(std::string const &);

    bool isKeyGenerate() const;

    Data &getData();

  private:
    std::string                      m_key;
    crypto::Hash<crypto::AHash::MD5> m_crypto;
    Data                             m_data;
    std::int32_t                     m_xor;
  };
}
#endif // CPP_INDIE_STUDIO_SaveData_HPP
