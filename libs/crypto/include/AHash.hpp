#ifndef AHASH_HPP_
#define AHASH_HPP_

#include <cstdint>
#include <string>

namespace crypto
{
  class AHash
  {
  public:
    // List of available algorithms
    enum Algorithm
    {
      MD2 = 0,
      MD4,
      MD5,
      MD6_128, // TODO
      MD6_256, // TODO
      MD6_512, // TODO
      SHA1,
      SHA224,
      SHA256,
      SHA384, // TODO
      SHA512, // TODO
      NB_ALGORITHM
    };

    explicit AHash(AHash::Algorithm algo)
        : m_algo(algo), m_hashLength(AHash::getBlockSize(algo)), m_hashStr()
    {
    }
    ~AHash();

    std::string const &getHash() const;

    // Returns an algorithm name
    constexpr static std::string const &algorithmName(AHash::Algorithm algo)
    {
      return (_algorithmName[algo]);
    }

  protected:
    constexpr static std::int32_t md2BlockSize = 16;
    constexpr static std::int32_t md4BlockSize = 16;
    constexpr static std::int32_t md5BlockSize = 16;
    constexpr static std::int32_t sha1BlockSize = 20;
    constexpr static std::int32_t sha224BlockSize = 28;
    constexpr static std::int32_t sha256BlockSize = 32;
    constexpr static std::int32_t sha512BlockSize = 64;

    // TODO
    constexpr static std::int32_t md6_128BlockSize = 1;
    constexpr static std::int32_t md6_256BlockSize = 1;
    constexpr static std::int32_t md6_512BlockSize = 1;
    constexpr static std::int32_t sha384BlockSize = 1;

    constexpr static std::int32_t getBlockSize(AHash::Algorithm algo)
    {
      return (_blockSize[algo]);
    }
    static std::string const            _algorithmName[];
    constexpr static std::int32_t const _blockSize[] = {
        AHash::md2BlockSize,     AHash::md4BlockSize,
        AHash::md5BlockSize,     AHash::md6_128BlockSize,
        AHash::md6_256BlockSize, AHash::md6_512BlockSize,
        AHash::sha1BlockSize,    AHash::sha224BlockSize,
        AHash::sha256BlockSize,  AHash::sha384BlockSize,
        AHash::sha512BlockSize};
    void calculateString(std::uint8_t const *hash);

    Algorithm    m_algo;
    std::int32_t m_hashLength;
    std::string  m_hashStr;
  };
}

std::ostream &operator<<(std::ostream &, crypto::AHash const &);

#endif // !AHASH_HPP_
