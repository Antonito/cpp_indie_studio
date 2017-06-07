#ifndef HASH_HPP_
#define HASH_HPP_

#include <iostream>
#include <cstdint>
#include <array>
#include <string>
#include "AHash.hpp"

// Disable clang warning for templated class padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

namespace crypto
{
  // Hash utility
  // Only works in Little Endian right now
  template <AHash::Algorithm A>
  class Hash : public AHash
  {
  public:
    explicit Hash();
    ~Hash();

    bool compute(std::uint8_t const *data, std::size_t const len);

  private:
    bool computeMD2(std::uint8_t const *data, std::size_t const len);
    bool computeMD4(std::uint8_t const *data, std::size_t const len);
    bool computeMD5(std::uint8_t const *data, std::size_t const len);
    bool computeSHA1(std::uint8_t const *data, std::size_t const len);
    bool computeSHA224(std::uint8_t const *data, std::size_t const len);
    bool computeSHA256(std::uint8_t const *data, std::size_t const len);
    bool computeSHA512(std::uint8_t const *data, std::size_t const len);

    struct md2Context
    {
      std::uint8_t data[md2BlockSize];
      std::uint8_t state[md2BlockSize * 3];
      std::uint8_t checksum[md2BlockSize];
      std::int32_t len;
    };

    struct md4Context
    {
      std::uint8_t  data[md4BlockSize * 4];
      std::uint32_t state[4];
      std::uint32_t count[2];
    };

    struct md5Context
    {
      std::uint8_t  data[md5BlockSize * 4];
      std::uint64_t bitlen;
      std::uint32_t state[4];
      std::uint32_t datalen;

    private:
      std::array<std::uint8_t, 4> __padding;
    };

    struct sha1Context
    {
      std::uint8_t  data[64];
      std::uint64_t bitlen;
      std::uint32_t state[5];
      std::uint32_t k[4];
      std::uint32_t datalen;

    private:
      std::array<std::uint8_t, 8> __padding;
    };

    struct sha256Context
    {
      std::uint8_t  data[64];
      std::uint64_t bitlen;
      std::uint32_t state[8];
      std::uint32_t datalen;

    private:
      std::array<std::uint8_t, 4> __padding;
    };

    struct sha512Context
    {
      std::uint8_t  data[128];
      std::uint64_t state[8];
      std::uint64_t bitlen;
      std::uint32_t datalen;
    };

    // Specific methods
    void md2Transform(md2Context &ctx, std::uint8_t const *data);
    void md4Transform(md4Context &ctx, std::uint8_t const *data);
    void md4Update(md4Context &ctx, std::uint8_t const *data,
                   std::size_t const len);
    void md5Transform(md5Context &ctx, std::uint8_t const *data);
    void sha1Transform(sha1Context &ctx, std::uint8_t const *data);
    void sha256Transform(sha256Context &ctx, std::uint8_t const *data);
    void sha512Transform(sha512Context &ctx, std::uint8_t const *data);

    std::array<std::uint8_t, _blockSize[A]> m_hash;
  };

#if defined(__linux__) || defined(__APPLE__)
  // Template definition for Linux and OSX
  extern template Hash<AHash::Algorithm::MD2>::Hash();
  extern template Hash<AHash::Algorithm::MD2>::~Hash();
  extern template bool
      Hash<AHash::Algorithm::MD2>::compute(std::uint8_t const *data,
                                           std::size_t const   len);

  extern template Hash<AHash::Algorithm::MD4>::Hash();
  extern template Hash<AHash::Algorithm::MD4>::~Hash();
  extern template bool
      Hash<AHash::Algorithm::MD4>::compute(std::uint8_t const *data,
                                           std::size_t const   len);

  extern template Hash<AHash::Algorithm::MD5>::Hash();
  extern template Hash<AHash::Algorithm::MD5>::~Hash();
  extern template bool
      Hash<AHash::Algorithm::MD5>::compute(std::uint8_t const *data,
                                           std::size_t const   len);

  extern template Hash<AHash::Algorithm::MD6_128>::Hash();
  extern template Hash<AHash::Algorithm::MD6_128>::~Hash();
  extern template bool
      Hash<AHash::Algorithm::MD6_128>::compute(std::uint8_t const *data,
                                               std::size_t const   len);

  extern template Hash<AHash::Algorithm::MD6_256>::Hash();
  extern template Hash<AHash::Algorithm::MD6_256>::~Hash();
  extern template bool
      Hash<AHash::Algorithm::MD6_256>::compute(std::uint8_t const *data,
                                               std::size_t const   len);

  extern template Hash<AHash::Algorithm::MD6_512>::Hash();
  extern template Hash<AHash::Algorithm::MD6_512>::~Hash();
  extern template bool
      Hash<AHash::Algorithm::MD6_512>::compute(std::uint8_t const *data,
                                               std::size_t const   len);

  extern template Hash<AHash::Algorithm::SHA1>::Hash();
  extern template Hash<AHash::Algorithm::SHA1>::~Hash();
  extern template bool
      Hash<AHash::Algorithm::SHA1>::compute(std::uint8_t const *data,
                                            std::size_t const   len);

  extern template Hash<AHash::Algorithm::SHA224>::Hash();
  extern template Hash<AHash::Algorithm::SHA224>::~Hash();
  extern template bool
      Hash<AHash::Algorithm::SHA224>::compute(std::uint8_t const *data,
                                              std::size_t const   len);

  extern template Hash<AHash::Algorithm::SHA256>::Hash();
  extern template Hash<AHash::Algorithm::SHA256>::~Hash();
  extern template bool
      Hash<AHash::Algorithm::SHA256>::compute(std::uint8_t const *data,
                                              std::size_t const   len);

  extern template Hash<AHash::Algorithm::SHA384>::Hash();
  extern template Hash<AHash::Algorithm::SHA384>::~Hash();
  extern template bool
      Hash<AHash::Algorithm::SHA384>::compute(std::uint8_t const *data,
                                              std::size_t const   len);

  extern template Hash<AHash::Algorithm::SHA512>::Hash();
  extern template Hash<AHash::Algorithm::SHA512>::~Hash();
  extern template bool
      Hash<AHash::Algorithm::SHA512>::compute(std::uint8_t const *data,
                                              std::size_t const   len);
#endif
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !HASH_HPP_
