#ifndef CIPHER_HPP_
#define CIPHER_HPP_

#include <cstdint>
#include <string>

namespace crypto
{
  class Cipher
  {
  public:
    enum Algorithm
    {
      BASE64 = 0,
      NB_ALGORITHM
    };

    constexpr explicit Cipher(Cipher::Algorithm algo) : m_algo(algo)
    {
    }

    ~Cipher();

    constexpr static std::string const &algorithmName(Cipher::Algorithm algo)
    {
      return (_algorithmName[algo]);
    }

    std::string encode(std::uint8_t const *data, std::size_t const len) const;
    std::string decode(std::uint8_t const *data, std::size_t const len) const;

  private:
    static std::string const _algorithmName[];

    std::string _base64Encode(std::uint8_t const *data,
                              std::size_t const   len) const;
    std::string _base64Decode(std::uint8_t const *data,
                              std::size_t const   len) const;
    Cipher::Algorithm const m_algo;
  };
}

#endif // !CIPHER_HPP_
