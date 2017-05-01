#include "crypto_stdafx.hpp"
#include <sstream>
#include <iomanip>
#include "AHash.hpp"

namespace crypto
{
  // Instanciation of block size
  constexpr std::int32_t       AHash::md2BlockSize;
  constexpr std::int32_t       AHash::md4BlockSize;
  constexpr std::int32_t       AHash::md5BlockSize;
  constexpr std::int32_t       AHash::md6_128BlockSize;
  constexpr std::int32_t       AHash::md6_256BlockSize;
  constexpr std::int32_t       AHash::md6_512BlockSize;
  constexpr std::int32_t       AHash::sha1BlockSize;
  constexpr std::int32_t       AHash::sha224BlockSize;
  constexpr std::int32_t       AHash::sha256BlockSize;
  constexpr std::int32_t       AHash::sha384BlockSize;
  constexpr std::int32_t       AHash::sha512BlockSize;
  constexpr std::int32_t const AHash::_blockSize[];

  // List of all (to be) implemented algorithm
  std::string const AHash::_algorithmName[] = {
      "MD2",  "MD4",    "MD5",    "MD6-128", "MD6-256", "MD6-512",
      "SHA1", "SHA224", "SHA256", "SHA384",  "SHA512"};

  AHash::~AHash()
  {
  }

  // Returns the generated hash string
  std::string const &AHash::getHash() const
  {
    return (m_hashStr);
  }

  // Compute a hash string from an already computed buffer
  // Parameter cannot be nullptr
  void AHash::calculateString(std::uint8_t const *hash)
  {
    std::stringstream stream;

    m_hashStr.clear();
    for (std::int32_t i = 0; i < m_hashLength; i++)
      {
	stream << std::hex << std::setfill('0') << std::setw(2)
	       << static_cast<int>(hash[i]);
      }
    m_hashStr = stream.str();
  }
}

// Print a stringified hash
std::ostream &operator<<(std::ostream &stream, crypto::AHash const &hash)
{
  stream << hash.getHash();
  return (stream);
}
