#include "crypto_stdafx.hpp"

// Disable clang warning for templated class padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

#if defined(_WIN32) && !defined(__on__linux__)
#include <Winsock2.h>
#endif

#include <exception>
#include <cassert>
#include <functional>
#include <cstring>
#include "Hash.hpp"
#include "Endian.hpp"

namespace crypto
{
  template <AHash::Algorithm A>
  Hash<A>::Hash() : AHash(A), m_hash()
  {
  }

  template <AHash::Algorithm A>
  Hash<A>::~Hash()
  {
  }

  template <AHash::Algorithm A>
  bool Hash<A>::compute(std::uint8_t const *data, std::size_t const len)
  {
    bool ret = false;

    if (data == nullptr)
      {
	throw std::runtime_error("Data cannot be nullptr");
      }
    switch (m_algo)
      {
      case Hash::MD2:
	ret = computeMD2(data, len);
	break;
      case Hash::MD4:
	ret = computeMD4(data, len);
	break;
      case Hash::MD5:
	ret = computeMD5(data, len);
	break;
      case Hash::SHA1:
	ret = computeSHA1(data, len);
	break;
      case Hash::SHA224:
	ret = computeSHA224(data, len);
	break;
      case Hash::SHA256:
	ret = computeSHA256(data, len);
	break;
      case Hash::SHA512:
	ret = computeSHA512(data, len);
	break;
      case Hash::MD6_128:
      case Hash::MD6_256:
      case Hash::MD6_512:
      case Hash::SHA384:
      case Hash::NB_ALGORITHM:
	throw std::runtime_error("Algorithm not implemented.");
      }
    if (ret == true)
      {
	calculateString(m_hash.data());
      }
    return (ret);
  }

  // Class instanciation
  template class Hash<AHash::MD2>;
  template class Hash<AHash::MD4>;
  template class Hash<AHash::MD5>;
  template class Hash<AHash::MD6_128>;
  template class Hash<AHash::MD6_256>;
  template class Hash<AHash::MD6_512>;
  template class Hash<AHash::SHA1>;
  template class Hash<AHash::SHA224>;
  template class Hash<AHash::SHA256>;
  template class Hash<AHash::SHA384>;
  template class Hash<AHash::SHA512>;

  // MD2 Implementation
  static std::uint8_t const md2HashTable[256] = {
      41,  46,  67,  201, 162, 216, 124, 1,   61,  54,  84,  161, 236, 240,
      6,   19,  98,  167, 5,   243, 192, 199, 115, 140, 152, 147, 43,  217,
      188, 76,  130, 202, 30,  155, 87,  60,  253, 212, 224, 22,  103, 66,
      111, 24,  138, 23,  229, 18,  190, 78,  196, 214, 218, 158, 222, 73,
      160, 251, 245, 142, 187, 47,  238, 122, 169, 104, 121, 145, 21,  178,
      7,   63,  148, 194, 16,  137, 11,  34,  95,  33,  128, 127, 93,  154,
      90,  144, 50,  39,  53,  62,  204, 231, 191, 247, 151, 3,   255, 25,
      48,  179, 72,  165, 181, 209, 215, 94,  146, 42,  172, 86,  170, 198,
      79,  184, 56,  210, 150, 164, 125, 182, 118, 252, 107, 226, 156, 116,
      4,   241, 69,  157, 112, 89,  100, 113, 135, 32,  134, 91,  207, 101,
      230, 45,  168, 2,   27,  96,  37,  173, 174, 176, 185, 246, 28,  70,
      97,  105, 52,  64,  126, 15,  85,  71,  163, 35,  221, 81,  175, 58,
      195, 92,  249, 206, 186, 197, 234, 38,  44,  83,  13,  110, 133, 40,
      132, 9,   211, 223, 205, 244, 65,  129, 77,  82,  106, 220, 55,  200,
      108, 193, 171, 250, 36,  225, 123, 8,   12,  189, 177, 74,  120, 136,
      149, 139, 227, 99,  232, 109, 233, 203, 213, 254, 59,  0,   29,  57,
      242, 239, 183, 14,  102, 88,  208, 228, 166, 119, 114, 248, 235, 117,
      75,  10,  49,  68,  80,  180, 143, 237, 31,  26,  219, 153, 141, 51,
      159, 17,  131, 20};

  template <AHash::Algorithm A>
  void Hash<A>::md2Transform(md2Context &ctx, std::uint8_t const *data)
  {
    std::int32_t tmp = 0;

    for (std::int32_t i = 0; i < AHash::md2BlockSize; ++i)
      {
	ctx.state[i + AHash::md2BlockSize] = data[i];
	ctx.state[i + 2 * AHash::md2BlockSize] =
	    ctx.state[i + AHash::md2BlockSize] ^ ctx.state[i];
      }

    for (std::int32_t i = 0; i < AHash::md2BlockSize + 2; ++i)
      {
	for (std::int32_t j = 0; j < AHash::md2BlockSize * 3; ++j)
	  {
	    ctx.state[j] ^= md2HashTable[tmp];
	    tmp = ctx.state[j];
	  }
	tmp = (tmp + i) & 0xFF;
      }

    tmp = ctx.checksum[15];
    for (std::int32_t i = 0; i < AHash::md2BlockSize; ++i)
      {
	ctx.checksum[i] ^= md2HashTable[data[i] ^ tmp];
	tmp = ctx.checksum[i];
      }
  }

  template <AHash::Algorithm A>
  bool Hash<A>::computeMD2(std::uint8_t const *data, std::size_t const len)
  {
    md2Context   ctx = {};
    std::int32_t pad = 0;

    // Update context
    for (std::size_t i = 0; i < len; ++i)
      {
	ctx.data[ctx.len] = data[i];
	++ctx.len;
	if (ctx.len == AHash::md2BlockSize)
	  {
	    md2Transform(ctx, ctx.data);
	    ctx.len = 0;
	  }
      }

    // Padding
    pad = AHash::md2BlockSize - ctx.len;
    while (ctx.len < AHash::md2BlockSize)
      {
	ctx.data[ctx.len] = static_cast<std::uint8_t>(pad);
	++ctx.len;
      }
    md2Transform(ctx, ctx.data);
    md2Transform(ctx, ctx.checksum);

    // Fill result
    std::memcpy(m_hash.data(), ctx.state, AHash::md2BlockSize);
    return (true);
  }

  // MD4 Implementation
  template <AHash::Algorithm A>
  void Hash<A>::md4Transform(md4Context &ctx, std::uint8_t const *data)
  {
    // Computation defined in RFC 1320
    typedef std::function<void(std::uint32_t &, std::uint32_t const &,
                               std::uint32_t const &, std::uint32_t const &,
                               std::uint32_t const &, std::uint32_t const)>
                     MD4Computation_t;
    MD4Computation_t FF = [](std::uint32_t &a, std::uint32_t const &b,
                             std::uint32_t const &c, std::uint32_t const &d,
                             std::uint32_t const &x, std::uint32_t const s) {
      a += ((b & c) | (~b & d)) + x;
      a = (a << s) | (a >> (32 - s));
    };
    MD4Computation_t GG = [](std::uint32_t &a, std::uint32_t const &b,
                             std::uint32_t const &c, std::uint32_t const &d,
                             std::uint32_t const &x, std::uint32_t const s) {
      a += ((b & c) | (b & d) | (c & d)) + x +
           static_cast<std::uint32_t>(0x5a827999);
      a = (a << s) | (a >> (32 - s));
    };
    MD4Computation_t HH = [](std::uint32_t &a, std::uint32_t const &b,
                             std::uint32_t const &c, std::uint32_t const &d,
                             std::uint32_t const &x, std::uint32_t const s) {
      a += (b ^ c ^ d) + x + static_cast<std::uint32_t>(0x6ed9eba1);
      a = (a << s) | (a >> (32 - s));
    };
    std::uint32_t a, b, c, d, m[AHash::md4BlockSize];

    a = ctx.state[0];
    b = ctx.state[1];
    c = ctx.state[2];
    d = ctx.state[3];

    // Deal with endianness
    if (Endian::isLittle())
      {
	for (std::uint32_t i = 0, j = 0; i < AHash::md4BlockSize; i++, j += 4)
	  {
	    m[i] = static_cast<std::uint32_t>((data[j]) + (data[j + 1] << 8) +
	                                      (data[j + 2] << 16) +
	                                      (data[j + 3] << 24));
	  }
      }

    FF(a, b, c, d, m[0], 3);
    FF(d, a, b, c, m[1], 7);
    FF(c, d, a, b, m[2], 11);
    FF(b, c, d, a, m[3], 19);
    FF(a, b, c, d, m[4], 3);
    FF(d, a, b, c, m[5], 7);
    FF(c, d, a, b, m[6], 11);
    FF(b, c, d, a, m[7], 19);
    FF(a, b, c, d, m[8], 3);
    FF(d, a, b, c, m[9], 7);
    FF(c, d, a, b, m[10], 11);
    FF(b, c, d, a, m[11], 19);
    FF(a, b, c, d, m[12], 3);
    FF(d, a, b, c, m[13], 7);
    FF(c, d, a, b, m[14], 11);
    FF(b, c, d, a, m[15], 19);

    GG(a, b, c, d, m[0], 3);
    GG(d, a, b, c, m[4], 5);
    GG(c, d, a, b, m[8], 9);
    GG(b, c, d, a, m[12], 13);
    GG(a, b, c, d, m[1], 3);
    GG(d, a, b, c, m[5], 5);
    GG(c, d, a, b, m[9], 9);
    GG(b, c, d, a, m[13], 13);
    GG(a, b, c, d, m[2], 3);
    GG(d, a, b, c, m[6], 5);
    GG(c, d, a, b, m[10], 9);
    GG(b, c, d, a, m[14], 13);
    GG(a, b, c, d, m[3], 3);
    GG(d, a, b, c, m[7], 5);
    GG(c, d, a, b, m[11], 9);
    GG(b, c, d, a, m[15], 13);

    HH(a, b, c, d, m[0], 3);
    HH(d, a, b, c, m[8], 9);
    HH(c, d, a, b, m[4], 11);
    HH(b, c, d, a, m[12], 15);
    HH(a, b, c, d, m[2], 3);
    HH(d, a, b, c, m[10], 9);
    HH(c, d, a, b, m[6], 11);
    HH(b, c, d, a, m[14], 15);
    HH(a, b, c, d, m[1], 3);
    HH(d, a, b, c, m[9], 9);
    HH(c, d, a, b, m[5], 11);
    HH(b, c, d, a, m[13], 15);
    HH(a, b, c, d, m[3], 3);
    HH(d, a, b, c, m[11], 9);
    HH(c, d, a, b, m[7], 11);
    HH(b, c, d, a, m[15], 15);

    ctx.state[0] += a;
    ctx.state[1] += b;
    ctx.state[2] += c;
    ctx.state[3] += d;
  }

  static std::uint8_t md4Padding[64] = {
      0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  template <AHash::Algorithm A>
  void Hash<A>::md4Update(md4Context &ctx, std::uint8_t const *data,
                          std::size_t const len)
  {
    std::uint32_t ndx = (ctx.count[0] >> 3) & 0x3F;
    std::uint32_t i = 0;

    ctx.count[0] += static_cast<std::uint32_t>(len) << 3;
    if (ctx.count[0] < (static_cast<std::uint32_t>(len) << 3))
      {
	++ctx.count[1];
      }
    ctx.count[1] += static_cast<std::uint32_t>(len) >> 29;
    std::uint32_t tmp = 64 - ndx;
    if (len >= tmp)
      {
	std::memcpy(&ctx.data[ndx], data, tmp);
	md4Transform(ctx, ctx.data);
	i = tmp;
	while (i + 63 < len)
	  {
	    md4Transform(ctx, &data[i]);
	    i += 64;
	  }
	ndx = 0;
      }
    std::memcpy(&ctx.data[ndx], &data[i], len - i);
  }

  template <AHash::Algorithm A>
  bool Hash<A>::computeMD4(std::uint8_t const *data, std::size_t const len)
  {
    md4Context ctx = {};
    std::function<void(std::uint8_t *, std::uint32_t *, std::int32_t)> encode =
        [&](std::uint8_t *out, uint32_t *in, std::int32_t _len) {
          for (std::int32_t i = 0, j = 0; j < _len; ++i, j += 4)
	    {
	      out[j] = static_cast<std::uint8_t>((in[i] & 0xff));
	      out[j + 1] = static_cast<std::uint8_t>(((in[i] >> 8) & 0xff));
	      out[j + 2] = static_cast<std::uint8_t>(((in[i] >> 16) & 0xff));
	      out[j + 3] = static_cast<std::uint8_t>(((in[i] >> 24) & 0xff));
	    }
        };

    ctx.state[0] = 0x67452301;
    ctx.state[1] = 0xEFCDAB89;
    ctx.state[2] = 0x98BADCFE;
    ctx.state[3] = 0x10325476;

    // Update context
    md4Update(ctx, data, len);

    // Padding
    std::uint8_t bak[8];
    encode(bak, ctx.count, 8);
    std::uint32_t ndx = (ctx.count[0] >> 3) & 0x3f;
    md4Update(ctx, md4Padding, (ndx < 56) ? (56 - ndx) : (120 - ndx));
    md4Update(ctx, bak, 8);

    // Deal with endinanness
    if (Endian::isLittle())
      {
	for (std::uint32_t i = 0; i < 4; ++i)
	  {
	    m_hash[i] = static_cast<std::uint8_t>((ctx.state[0] >> (i * 8)) &
	                                          0x000000FF);
	    m_hash[i + 4] = static_cast<std::uint8_t>(
	        (ctx.state[1] >> (i * 8)) & 0x000000FF);
	    m_hash[i + 8] = static_cast<std::uint8_t>(
	        (ctx.state[2] >> (i * 8)) & 0x000000FF);
	    m_hash[i + 12] = static_cast<std::uint8_t>(
	        (ctx.state[3] >> (i * 8)) & 0x000000FF);
	  }
      }
    return (true);
  }

  // MD5 Implementation
  template <AHash::Algorithm A>
  void Hash<A>::md5Transform(md5Context &ctx, std::uint8_t const *data)
  {
    // Computation defined in RFC 1321
    typedef std::function<void(std::uint32_t &, std::uint32_t const &,
                               std::uint32_t const &, std::uint32_t const &,
                               std::uint32_t const &, std::uint32_t const &,
                               std::uint32_t const &)>
                     MD5Computation_t;
    MD5Computation_t FF = [](std::uint32_t &a, std::uint32_t const &b,
                             std::uint32_t const &c, std::uint32_t const &d,
                             std::uint32_t const &m, std::uint32_t const &s,
                             std::uint32_t const &t) {
      a += ((b & c) | (~b & d)) + m + t;
      a = b + ((a << s) | (a >> (32 - s)));
    };
    MD5Computation_t GG = [](std::uint32_t &a, std::uint32_t const &b,
                             std::uint32_t const &c, std::uint32_t const &d,
                             std::uint32_t const &m, std::uint32_t const &s,
                             std::uint32_t const &t) {
      a += ((b & d) | (c & ~d)) + m + t;
      a = b + ((a << s) | (a >> (32 - s)));
    };
    MD5Computation_t HH = [](std::uint32_t &a, std::uint32_t const &b,
                             std::uint32_t const &c, std::uint32_t const &d,
                             std::uint32_t const &m, std::uint32_t const &s,
                             std::uint32_t const &t) {
      a += (b ^ c ^ d) + m + t;
      a = b + ((a << s) | (a >> (32 - s)));
    };
    MD5Computation_t II = [](std::uint32_t &a, std::uint32_t const &b,
                             std::uint32_t const &c, std::uint32_t const &d,
                             std::uint32_t const &m, std::uint32_t const &s,
                             std::uint32_t const &t) {
      a += (c ^ (b | ~d)) + m + t;
      a = b + ((a << s) | (a >> (32 - s)));
    };
    std::uint32_t a, b, c, d, m[AHash::md5BlockSize];

    // Endianness
    if (Endian::isLittle())
      {
	for (std::uint32_t i = 0, j = 0; i < md5BlockSize; ++i, j += 4)
	  {
	    m[i] = static_cast<std::uint32_t>((data[j]) + (data[j + 1] << 8) +
	                                      (data[j + 2] << 16) +
	                                      (data[j + 3] << 24));
	  }
      }
    a = ctx.state[0];
    b = ctx.state[1];
    c = ctx.state[2];
    d = ctx.state[3];

    for (std::int32_t i = 0; i < AHash::md5BlockSize; ++i)
      {
	std::uint32_t const _a[] = {7, 12, 17, 22};
	std::uint32_t const value[] = {
	    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821};
	std::uint32_t tmp;

	FF(a, b, c, d, m[i], _a[i % 4], value[i]);
	tmp = a;
	a = d;
	d = c;
	c = b;
	b = tmp;
      }

    // Compute stuff
    GG(a, b, c, d, m[1], 5, 0xf61e2562);
    GG(d, a, b, c, m[6], 9, 0xc040b340);
    GG(c, d, a, b, m[11], 14, 0x265e5a51);
    GG(b, c, d, a, m[0], 20, 0xe9b6c7aa);
    GG(a, b, c, d, m[5], 5, 0xd62f105d);
    GG(d, a, b, c, m[10], 9, 0x02441453);
    GG(c, d, a, b, m[15], 14, 0xd8a1e681);
    GG(b, c, d, a, m[4], 20, 0xe7d3fbc8);
    GG(a, b, c, d, m[9], 5, 0x21e1cde6);
    GG(d, a, b, c, m[14], 9, 0xc33707d6);
    GG(c, d, a, b, m[3], 14, 0xf4d50d87);
    GG(b, c, d, a, m[8], 20, 0x455a14ed);
    GG(a, b, c, d, m[13], 5, 0xa9e3e905);
    GG(d, a, b, c, m[2], 9, 0xfcefa3f8);
    GG(c, d, a, b, m[7], 14, 0x676f02d9);
    GG(b, c, d, a, m[12], 20, 0x8d2a4c8a);

    HH(a, b, c, d, m[5], 4, 0xfffa3942);
    HH(d, a, b, c, m[8], 11, 0x8771f681);
    HH(c, d, a, b, m[11], 16, 0x6d9d6122);
    HH(b, c, d, a, m[14], 23, 0xfde5380c);
    HH(a, b, c, d, m[1], 4, 0xa4beea44);
    HH(d, a, b, c, m[4], 11, 0x4bdecfa9);
    HH(c, d, a, b, m[7], 16, 0xf6bb4b60);
    HH(b, c, d, a, m[10], 23, 0xbebfbc70);
    HH(a, b, c, d, m[13], 4, 0x289b7ec6);
    HH(d, a, b, c, m[0], 11, 0xeaa127fa);
    HH(c, d, a, b, m[3], 16, 0xd4ef3085);
    HH(b, c, d, a, m[6], 23, 0x04881d05);
    HH(a, b, c, d, m[9], 4, 0xd9d4d039);
    HH(d, a, b, c, m[12], 11, 0xe6db99e5);
    HH(c, d, a, b, m[15], 16, 0x1fa27cf8);
    HH(b, c, d, a, m[2], 23, 0xc4ac5665);

    II(a, b, c, d, m[0], 6, 0xf4292244);
    II(d, a, b, c, m[7], 10, 0x432aff97);
    II(c, d, a, b, m[14], 15, 0xab9423a7);
    II(b, c, d, a, m[5], 21, 0xfc93a039);
    II(a, b, c, d, m[12], 6, 0x655b59c3);
    II(d, a, b, c, m[3], 10, 0x8f0ccc92);
    II(c, d, a, b, m[10], 15, 0xffeff47d);
    II(b, c, d, a, m[1], 21, 0x85845dd1);
    II(a, b, c, d, m[8], 6, 0x6fa87e4f);
    II(d, a, b, c, m[15], 10, 0xfe2ce6e0);
    II(c, d, a, b, m[6], 15, 0xa3014314);
    II(b, c, d, a, m[13], 21, 0x4e0811a1);
    II(a, b, c, d, m[4], 6, 0xf7537e82);
    II(d, a, b, c, m[11], 10, 0xbd3af235);
    II(c, d, a, b, m[2], 15, 0x2ad7d2bb);
    II(b, c, d, a, m[9], 21, 0xeb86d391);

    // Update state
    ctx.state[0] += a;
    ctx.state[1] += b;
    ctx.state[2] += c;
    ctx.state[3] += d;
  }

  template <AHash::Algorithm A>
  bool Hash<A>::computeMD5(std::uint8_t const *data, std::size_t const len)
  {
    md5Context    ctx = {};
    std::uint32_t pad = 0;

    ctx.state[0] = 0x67452301;
    ctx.state[1] = 0xEFCDAB89;
    ctx.state[2] = 0x98BADCFE;
    ctx.state[3] = 0x10325476;

    // Update context
    for (std::size_t i = 0; i < len; ++i)
      {
	ctx.data[ctx.datalen] = data[i];
	++ctx.datalen;
	if (ctx.datalen == AHash::md5BlockSize * 4)
	  {
	    md5Transform(ctx, ctx.data);
	    ctx.bitlen += 512;
	    ctx.datalen = 0;
	  }
      }

    // Padding
    pad = ctx.datalen;
    if (ctx.datalen < 56)
      {
	ctx.data[pad] = 0x80;
	++pad;
	while (pad < 56)
	  {
	    ctx.data[pad] = 0;
	    ++pad;
	  }
      }
    else if (ctx.datalen >= 56)
      {
	ctx.data[pad] = 0x80;
	++pad;
	while (pad < 64)
	  {
	    ctx.data[pad] = 0;
	    ++pad;
	  }
	md5Transform(ctx, ctx.data);
	std::memset(ctx.data, 0, 56);
      }
    ctx.bitlen += ctx.datalen * 8;
    ctx.data[56] = static_cast<uint8_t>(ctx.bitlen);
    ctx.data[57] = static_cast<uint8_t>(ctx.bitlen >> 8);
    ctx.data[58] = static_cast<uint8_t>(ctx.bitlen >> 16);
    ctx.data[59] = static_cast<uint8_t>(ctx.bitlen >> 24);
    ctx.data[60] = static_cast<uint8_t>(ctx.bitlen >> 32);
    ctx.data[61] = static_cast<uint8_t>(ctx.bitlen >> 40);
    ctx.data[62] = static_cast<uint8_t>(ctx.bitlen >> 48);
    ctx.data[63] = static_cast<uint8_t>(ctx.bitlen >> 56);
    md5Transform(ctx, ctx.data);

    // Deal with endinanness
    if (Endian::isLittle())
      {
	for (std::uint32_t i = 0; i < 4; ++i)
	  {
	    m_hash[i] = (ctx.state[0] >> (i * 8)) & 0x000000FF;
	    m_hash[i + 4] = (ctx.state[1] >> (i * 8)) & 0x000000FF;
	    m_hash[i + 8] = (ctx.state[2] >> (i * 8)) & 0x000000FF;
	    m_hash[i + 12] = (ctx.state[3] >> (i * 8)) & 0x000000FF;
	  }
      }
    return (true);
  }

// MD6-128 implementation
// MD6-256 implementation
// MD6-512 implementation
// SHA1 implementation
#define ROTATE_LEFT(a, b) ((a << b) | (a >> (32 - b)))

  template <AHash::Algorithm A>
  void Hash<A>::sha1Transform(sha1Context &ctx, std::uint8_t const *data)
  {
    std::uint32_t a, b, c, d, e, m[80], i;

    i = 0;
    if (Endian::isLittle())
      {
	for (std::uint32_t j = 0; i < 16; ++i, j += 4)
	  {
	    m[i] = static_cast<std::uint32_t>(
	        (data[j] << 24) + (data[j + 1] << 16) + (data[j + 2] << 8) +
	        (data[j + 3]));
	  }
      }
    while (i < 80)
      {
	m[i] = (m[i - 3] ^ m[i - 8] ^ m[i - 14] ^ m[i - 16]);
	m[i] = (m[i] << 1) | (m[i] >> 31);
	++i;
      }

    a = ctx.state[0];
    b = ctx.state[1];
    c = ctx.state[2];
    d = ctx.state[3];
    e = ctx.state[4];
    i = 0;
    while (i < 20)
      {
	std::uint32_t t =
	    ROTATE_LEFT(a, 5) + ((b & c) ^ (~b & d)) + e + ctx.k[0] + m[i];

	e = d;
	d = c;
	c = ROTATE_LEFT(b, 30);
	b = a;
	a = t;
	++i;
      }
    while (i < 40)
      {
	std::uint32_t t =
	    ROTATE_LEFT(a, 5) + (b ^ c ^ d) + e + ctx.k[1] + m[i];
	e = d;
	d = c;
	c = ROTATE_LEFT(b, 30);
	b = a;
	a = t;
	++i;
      }
    while (i < 60)
      {
	std::uint32_t t = ROTATE_LEFT(a, 5) + ((b & c) ^ (b & d) ^ (c & d)) +
	                  e + ctx.k[2] + m[i];
	e = d;
	d = c;
	c = ROTATE_LEFT(b, 30);
	b = a;
	a = t;
	++i;
      }
    while (i < 80)
      {
	std::uint32_t t =
	    ROTATE_LEFT(a, 5) + (b ^ c ^ d) + e + ctx.k[3] + m[i];
	e = d;
	d = c;
	c = ROTATE_LEFT(b, 30);
	b = a;
	a = t;
	++i;
      }

    ctx.state[0] += a;
    ctx.state[1] += b;
    ctx.state[2] += c;
    ctx.state[3] += d;
    ctx.state[4] += e;
  }
#undef ROTLEFT

  template <AHash::Algorithm A>
  bool Hash<A>::computeSHA1(std::uint8_t const *data, std::size_t const len)
  {
    sha1Context ctx = {};

    ctx.state[0] = 0x67452301;
    ctx.state[1] = 0xEFCDAB89;
    ctx.state[2] = 0x98BADCFE;
    ctx.state[3] = 0x10325476;
    ctx.state[4] = 0xc3d2e1f0;
    ctx.k[0] = 0x5a827999;
    ctx.k[1] = 0x6ed9eba1;
    ctx.k[2] = 0x8f1bbcdc;
    ctx.k[3] = 0xca62c1d6;

    // Update
    for (std::size_t i = 0; i < len; ++i)
      {
	ctx.data[ctx.datalen] = data[i];
	++ctx.datalen;
	if (ctx.datalen == 64)
	  {
	    sha1Transform(ctx, ctx.data);
	    ctx.bitlen += 512;
	    ctx.datalen = 0;
	  }
      }

    // Padding
    std::uint32_t tmp = ctx.datalen;
    if (ctx.datalen < 56)
      {
	ctx.data[tmp] = 0x80;
	++tmp;
	while (tmp < 56)
	  {
	    ctx.data[tmp] = 0;
	    ++tmp;
	  }
      }
    else
      {
	ctx.data[tmp] = 0x80;
	while (tmp < 64)
	  {
	    ctx.data[tmp] = 0;
	    ++tmp;
	  }
	sha1Transform(ctx, ctx.data);
	std::memset(ctx.data, 0, 56);
      }

    ctx.bitlen += ctx.datalen * 8;
    ctx.data[63] = static_cast<std::uint8_t>(ctx.bitlen);
    ctx.data[62] = static_cast<std::uint8_t>(ctx.bitlen >> 8);
    ctx.data[61] = static_cast<std::uint8_t>(ctx.bitlen >> 16);
    ctx.data[60] = static_cast<std::uint8_t>(ctx.bitlen >> 24);
    ctx.data[59] = static_cast<std::uint8_t>(ctx.bitlen >> 32);
    ctx.data[58] = static_cast<std::uint8_t>(ctx.bitlen >> 40);
    ctx.data[57] = static_cast<std::uint8_t>(ctx.bitlen >> 48);
    ctx.data[56] = static_cast<std::uint8_t>(ctx.bitlen >> 56);
    sha1Transform(ctx, ctx.data);

    // Deal with endianness
    if (Endian::isLittle())
      {
	for (std::uint32_t i = 0; i < 4; ++i)
	  {
	    m_hash[i] = (ctx.state[0] >> (24 - i * 8)) & 0x000000FF;
	    m_hash[i + 4] = (ctx.state[1] >> (24 - i * 8)) & 0x000000FF;
	    m_hash[i + 8] = (ctx.state[2] >> (24 - i * 8)) & 0x000000FF;
	    m_hash[i + 12] = (ctx.state[3] >> (24 - i * 8)) & 0x000000FF;
	    m_hash[i + 16] = (ctx.state[4] >> (24 - i * 8)) & 0x000000FF;
	  }
      }
    return (true);
  }

// SHA224 - SHA256 implementation
#define ROTRIGHT(a, b) (((a) >> (b)) | ((a) << (32 - (b))))
#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x, 2) ^ ROTRIGHT(x, 13) ^ ROTRIGHT(x, 22))
#define EP1(x) (ROTRIGHT(x, 6) ^ ROTRIGHT(x, 11) ^ ROTRIGHT(x, 25))
#define SIG0(x) (ROTRIGHT(x, 7) ^ ROTRIGHT(x, 18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x, 17) ^ ROTRIGHT(x, 19) ^ ((x) >> 10))

  static std::uint32_t const hashTableSha256[64] = {
      0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
      0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
      0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
      0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
      0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
      0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
      0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
      0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
      0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
      0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
      0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

  template <AHash::Algorithm A>
  void Hash<A>::sha256Transform(sha256Context &ctx, std::uint8_t const *data)
  {
    std::uint32_t a, b, c, d, e, f, g, h, i, m[64];

    i = 0;
    if (Endian::isLittle())
      {
	for (std::uint32_t j = 0; i < 16; ++i, j += 4)
	  {
	    m[i] = static_cast<std::uint32_t>(
	        (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) |
	        (data[j + 3]));
	  }
      }
    while (i < 64)
      {
	m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];
	++i;
      }

    a = ctx.state[0];
    b = ctx.state[1];
    c = ctx.state[2];
    d = ctx.state[3];
    e = ctx.state[4];
    f = ctx.state[5];
    g = ctx.state[6];
    h = ctx.state[7];

    for (std::int32_t j = 0; j < 64; ++j)
      {
	std::uint32_t t1 =
	    h + EP1(e) + CH(e, f, g) + hashTableSha256[j] + m[j];
	std::uint32_t t2 = EP0(a) + MAJ(a, b, c);

	h = g;
	g = f;
	f = e;
	e = d + t1;
	d = c;
	c = b;
	b = a;
	a = t1 + t2;
      }

    ctx.state[0] += a;
    ctx.state[1] += b;
    ctx.state[2] += c;
    ctx.state[3] += d;
    ctx.state[4] += e;
    ctx.state[5] += f;
    ctx.state[6] += g;
    ctx.state[7] += h;
  }

  template <AHash::Algorithm A>
  bool Hash<A>::computeSHA224(std::uint8_t const *data, std::size_t const len)
  {
    sha256Context ctx = {};

    ctx.state[0] = 0xC1059ED8;
    ctx.state[1] = 0x367CD507;
    ctx.state[2] = 0x3070DD17;
    ctx.state[3] = 0xF70E5939;
    ctx.state[4] = 0xFFC00B31;
    ctx.state[5] = 0x68581511;
    ctx.state[6] = 0x64F98FA7;
    ctx.state[7] = 0xBEFA4FA4;

    // Update
    for (std::size_t i = 0; i < len; ++i)
      {
	ctx.data[ctx.datalen] = data[i];
	++ctx.datalen;
	if (ctx.datalen == 64)
	  {
	    sha256Transform(ctx, ctx.data);
	    ctx.bitlen += 512;
	    ctx.datalen = 0;
	  }
      }

    std::uint32_t tmp = ctx.datalen;
    if (ctx.datalen < 56)
      {
	ctx.data[tmp] = 0x80;
	++tmp;
	while (tmp < 56)
	  {
	    ctx.data[tmp] = 0;
	    ++tmp;
	  }
      }
    else
      {
	ctx.data[tmp] = 0x80;
	while (tmp < 64)
	  {
	    ctx.data[tmp] = 0;
	    ++tmp;
	  }
	sha256Transform(ctx, ctx.data);
	std::memset(ctx.data, 0, 56);
      }

    ctx.bitlen += ctx.datalen * 8;
    ctx.data[63] = static_cast<std::uint8_t>(ctx.bitlen);
    ctx.data[62] = static_cast<std::uint8_t>(ctx.bitlen >> 8);
    ctx.data[61] = static_cast<std::uint8_t>(ctx.bitlen >> 16);
    ctx.data[60] = static_cast<std::uint8_t>(ctx.bitlen >> 24);
    ctx.data[59] = static_cast<std::uint8_t>(ctx.bitlen >> 32);
    ctx.data[58] = static_cast<std::uint8_t>(ctx.bitlen >> 40);
    ctx.data[57] = static_cast<std::uint8_t>(ctx.bitlen >> 48);
    ctx.data[56] = static_cast<std::uint8_t>(ctx.bitlen >> 56);
    sha256Transform(ctx, ctx.data);

    // Deal with endianness
    if (Endian::isLittle())
      {
	for (std::uint32_t i = 0; i < AHash::sha224BlockSize; ++i)
	  {
	    m_hash[i] = static_cast<std::uint8_t>(ctx.state[i >> 2] >>
	                                          8 * (3 - (i & 0x3)));
	  }
      }
    return (true);
  }

  template <AHash::Algorithm A>
  bool Hash<A>::computeSHA256(std::uint8_t const *data, std::size_t const len)
  {
    sha256Context ctx = {};

    ctx.state[0] = 0x6a09e667;
    ctx.state[1] = 0xbb67ae85;
    ctx.state[2] = 0x3c6ef372;
    ctx.state[3] = 0xa54ff53a;
    ctx.state[4] = 0x510e527f;
    ctx.state[5] = 0x9b05688c;
    ctx.state[6] = 0x1f83d9ab;
    ctx.state[7] = 0x5be0cd19;

    // Update
    for (std::size_t i = 0; i < len; ++i)
      {
	ctx.data[ctx.datalen] = data[i];
	++ctx.datalen;
	if (ctx.datalen == 64)
	  {
	    sha256Transform(ctx, ctx.data);
	    ctx.bitlen += 512;
	    ctx.datalen = 0;
	  }
      }

    std::uint32_t tmp = ctx.datalen;
    if (ctx.datalen < 56)
      {
	ctx.data[tmp] = 0x80;
	++tmp;
	while (tmp < 56)
	  {
	    ctx.data[tmp] = 0;
	    ++tmp;
	  }
      }
    else
      {
	ctx.data[tmp] = 0x80;
	while (tmp < 64)
	  {
	    ctx.data[tmp] = 0;
	    ++tmp;
	  }
	sha256Transform(ctx, ctx.data);
	std::memset(ctx.data, 0, 56);
      }

    ctx.bitlen += ctx.datalen * 8;
    ctx.data[63] = static_cast<std::uint8_t>(ctx.bitlen);
    ctx.data[62] = static_cast<std::uint8_t>(ctx.bitlen >> 8);
    ctx.data[61] = static_cast<std::uint8_t>(ctx.bitlen >> 16);
    ctx.data[60] = static_cast<std::uint8_t>(ctx.bitlen >> 24);
    ctx.data[59] = static_cast<std::uint8_t>(ctx.bitlen >> 32);
    ctx.data[58] = static_cast<std::uint8_t>(ctx.bitlen >> 40);
    ctx.data[57] = static_cast<std::uint8_t>(ctx.bitlen >> 48);
    ctx.data[56] = static_cast<std::uint8_t>(ctx.bitlen >> 56);
    sha256Transform(ctx, ctx.data);

    // Deal with endianness
    if (Endian::isLittle())
      {
	for (std::uint32_t i = 0; i < 4; ++i)
	  {
	    m_hash[i] = (ctx.state[0] >> (24 - i * 8)) & 0x000000FF;
	    m_hash[i + 4] = (ctx.state[1] >> (24 - i * 8)) & 0x000000FF;
	    m_hash[i + 8] = (ctx.state[2] >> (24 - i * 8)) & 0x000000FF;
	    m_hash[i + 12] = (ctx.state[3] >> (24 - i * 8)) & 0x000000FF;
	    m_hash[i + 16] = (ctx.state[4] >> (24 - i * 8)) & 0x000000FF;
	    m_hash[i + 20] = (ctx.state[5] >> (24 - i * 8)) & 0x000000FF;
	    m_hash[i + 24] = (ctx.state[6] >> (24 - i * 8)) & 0x000000FF;
	    m_hash[i + 28] = (ctx.state[7] >> (24 - i * 8)) & 0x000000FF;
	  }
      }
    return (true);
  }

#undef ROTLEFT
#undef ROTRIGHT
#undef CH
#undef MAJ
#undef EP0
#undef EP1
#undef SIG0
#undef SIG1

  // SHA384 & SHA512 implementation
  static std::uint64_t const hashTableSha512[80] = {
      0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f,
      0xe9b5dba58189dbbc, 0x3956c25bf348b538, 0x59f111f1b605d019,
      0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242,
      0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
      0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
      0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
      0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 0x2de92c6f592b0275,
      0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
      0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f,
      0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
      0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc,
      0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
      0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6,
      0x92722c851482353b, 0xa2bfe8a14cf10364, 0xa81a664bbc423001,
      0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
      0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
      0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99,
      0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
      0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc,
      0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
      0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915,
      0xc67178f2e372532b, 0xca273eceea26619c, 0xd186b8c721c0c207,
      0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba,
      0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
      0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
      0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
      0x5fcb6fab3ad6faec, 0x6c44198c4a475817};

  /*
  #define W(t) m[(t)&0x0F]
  #define ROTLEFT(a, b) (((a) << (b)) | ((a) >> (64 - (b))))
  #define ROTRIGHT(a, b) (((a) >> (b)) | ((a) << (64 - (b))))
  #define CH(x, y, z) (((x) & (y)) | (~(x) & (z)))
  #define MAJ(x, y, z) (((x) & (y)) | ((x) & (z)) | ((y) & (z)))
  #define SIGMA1(x) (ROTRIGHT(x, 28) ^ ROTRIGHT(x, 34) ^ ROTRIGHT(x, 39))
  #define SIGMA2(x) (ROTRIGHT(x, 14) ^ ROTRIGHT(x, 18) ^ ROTRIGHT(x, 41))
  #define SIGMA3(x) (ROTRIGHT(x, 1) ^ ROTRIGHT(x, 8) ^ (x >> 7))
  #define SIGMA4(x) (ROTRIGHT(x, 19) ^ ROTRIGHT(x, 61) ^ (x >> 6))
  */

  template <AHash::Algorithm A>
  void Hash<A>::sha512Transform(sha512Context &ctx, std::uint8_t const *data)
  {
    (void)ctx, (void)data;
#if 0
    std::uint64_t a, b, c, d, e, f, g, h, i, m[16];

    i = 0;
    if (Endian::isLittle())
      {
	for (std::int32_t j = 0; j < 16; ++j)
	  {
	    std::uint64_t cur =
	        reinterpret_cast<std::uint64_t const *>(data)[j];
	    m[i] = htonll(cur);
	  }
      }

    a = ctx.state[0];
    b = ctx.state[1];
    c = ctx.state[2];
    d = ctx.state[3];
    e = ctx.state[4];
    f = ctx.state[5];
    g = ctx.state[6];
    h = ctx.state[7];

    for (std::int64_t j = 0; j < 80; ++j)
      {
	if (j <= 16)
	  {
	    W(j) += SIGMA4(W(j + 14)) + W(j + 9) + SIGMA3(W(j + 1));
	  }

	std::uint64_t t1 =
	    h + SIGMA2(e) + CH(e, f, g) + hashTableSha512[j] + W(j);
	std::uint64_t t2 = SIGMA1(a) + MAJ(a, b, c);

	h = g;
	g = f;
	f = e;
	e = d + t1;
	d = c;
	c = b;
	b = a;
	a = t1 + t2;
      }

    ctx.state[0] += a;
    ctx.state[1] += b;
    ctx.state[2] += c;
    ctx.state[3] += d;
    ctx.state[4] += e;
    ctx.state[5] += f;
    ctx.state[6] += g;
    ctx.state[7] += h;
#endif
  }

  /*
  #undef ROTLEFT
  #undef ROTRIGHT
  #undef CH
  #undef MAJ
  #undef SIGMA1
  #undef SIGMA2
  #undef SIGMA3
  #undef SIGMA4
  #undef W
  */

  template <AHash::Algorithm A>
  bool Hash<A>::computeSHA512(std::uint8_t const *data, std::size_t const len)
  {
    assert(0 && "Not implemented yet");
    (void)data, (void)len, (void)hashTableSha512;
    return (false);
#if 0
    sha512Context ctx = {};

    ctx.state[0] = 0x6a09e667f3bcc908;
    ctx.state[1] = 0xbb67ae8584caa73b;
    ctx.state[2] = 0x3c6ef372fe94f82b;
    ctx.state[3] = 0xa54ff53a5f1d36f1;
    ctx.state[4] = 0x510e527fade682d1;
    ctx.state[5] = 0x9b05688c2b3e6c1f;
    ctx.state[6] = 0x1f83d9abfb41bd6b;
    ctx.state[7] = 0x5be0cd19137e2179;

    // Update
    for (std::size_t i = 0; i < len; ++i)
      {
	ctx.data[ctx.datalen] = data[i];
	++ctx.datalen;
	if (ctx.datalen == 128)
	  {
	    sha512Transform(ctx, ctx.data);
	    ctx.bitlen += 1024;
	    ctx.datalen = 0;
	  }
      }

    std::uint64_t tmp = ctx.datalen;
    if (ctx.datalen < 112)
      {
	ctx.data[tmp] = 0x80;
	++tmp;
	while (tmp < 112)
	  {
	    ctx.data[tmp] = 0;
	    ++tmp;
	  }
      }
    else
      {
	ctx.data[tmp] = 0x80;
	while (tmp < 128)
	  {
	    ctx.data[tmp] = 0;
	    ++tmp;
	  }
	sha512Transform(ctx, ctx.data);
	std::memset(ctx.data, 0, 112);
      }

    ctx.bitlen += ctx.datalen * 8;
    ctx.data[63] = static_cast<std::uint8_t>(ctx.bitlen);
    ctx.data[62] = static_cast<std::uint8_t>(ctx.bitlen >> 8);
    ctx.data[61] = static_cast<std::uint8_t>(ctx.bitlen >> 16);
    ctx.data[60] = static_cast<std::uint8_t>(ctx.bitlen >> 24);
    ctx.data[59] = static_cast<std::uint8_t>(ctx.bitlen >> 32);
    ctx.data[58] = static_cast<std::uint8_t>(ctx.bitlen >> 40);
    ctx.data[57] = static_cast<std::uint8_t>(ctx.bitlen >> 48);
    ctx.data[56] = static_cast<std::uint8_t>(ctx.bitlen >> 56);
    sha512Transform(ctx, ctx.data);

    // Deal with endianness
    if (Endian::isLittle())
      {
	for (std::int32_t i = 0; i < 8; ++i)
	  {
	    m_hash[i] = (ctx.state[0] >> (56 - i * 8)) & 0x000000FF;
	    m_hash[i + 4] = (ctx.state[1] >> (56 - i * 8)) & 0x000000FF;
	    m_hash[i + 8] = (ctx.state[2] >> (56 - i * 8)) & 0x000000FF;
	    m_hash[i + 12] = (ctx.state[3] >> (56 - i * 8)) & 0x000000FF;
	    m_hash[i + 16] = (ctx.state[4] >> (56 - i * 8)) & 0x000000FF;
	    m_hash[i + 20] = (ctx.state[5] >> (56 - i * 8)) & 0x000000FF;
	    m_hash[i + 24] = (ctx.state[6] >> (56 - i * 8)) & 0x000000FF;
	    m_hash[i + 28] = (ctx.state[7] >> (56 - i * 8)) & 0x000000FF;
	  }
      }
    return (true);
#endif
  }
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif
