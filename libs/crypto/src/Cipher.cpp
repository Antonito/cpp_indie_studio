#include "crypto_stdafx.hpp"
#include <array>
#include <functional>
#include <cctype>
#include "Cipher.hpp"

namespace crypto
{
  std::string const Cipher::_algorithmName[] = {"Base64"};

  Cipher::~Cipher()
  {
  }

  std::string Cipher::encode(std::uint8_t const *data,
                             std::size_t const   len) const
  {
    switch (m_algo)
      {
      case Algorithm::BASE64:
	return (_base64Encode(data, len));
      case Algorithm::NB_ALGORITHM:
	throw std::runtime_error("Algorithm not supported");
      }
    return ("");
  }

  std::string Cipher::decode(std::uint8_t const *data,
                             std::size_t const   len) const
  {
    switch (m_algo)
      {
      case Algorithm::BASE64:
	return (_base64Decode(data, len));
      case Algorithm::NB_ALGORITHM:
	throw std::runtime_error("Algorithm not supported");
      }
    return ("");
  }

  // Base64 Implementation
  static std::string const _b64Table =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  std::string Cipher::_base64Encode(std::uint8_t const *data,
                                    std::size_t const   len) const
  {
    std::string ret;
    std::size_t i = 0;
    std::array<std::uint8_t, 3> ref3;

    // Fill string
    for (std::size_t _len = len; _len; _len--)
      {
	ref3[i] = *data;
	++i;
	++data;
	if (i == 3)
	  {
	    ret += static_cast<char>(
	        _b64Table[static_cast<std::uint32_t>((ref3[0] & 0xFC) >> 2)]);
	    ret += static_cast<char>(_b64Table[static_cast<std::uint32_t>(
	        ((ref3[0] & 0x03) << 4) + ((ref3[1] & 0xF0) >> 4))]);
	    ret += static_cast<char>(_b64Table[static_cast<std::uint32_t>(
	        ((ref3[1] & 0x0F) << 2) + ((ref3[2] & 0xC0) >> 6))]);
	    ret += static_cast<char>(
	        _b64Table[static_cast<std::uint32_t>(ref3[2] & 0x3F)]);
	    i = 0;
	  }
      }

    // Pad
    if (i)
      {
	std::array<std::uint8_t, 4> ref4;
	for (std::size_t j = i; j < 3; ++j)
	  {
	    ref3[j] = 0;
	  }
	ref4[0] = static_cast<std::uint8_t>((ref3[0] & 0xFC) >> 2);
	ref4[1] = static_cast<std::uint8_t>(((ref3[0] & 0x03) << 4) +
	                                    ((ref3[1] & 0xF0) >> 4));
	ref4[2] = static_cast<std::uint8_t>(((ref3[1] & 0x0F) << 2) +
	                                    ((ref3[2] & 0xC0) >> 6));
	ref4[3] = static_cast<std::uint8_t>(ref3[2] & 0x3F);
	for (std::size_t j = 0; j < i + 1; ++j)
	  {
	    ret += _b64Table[ref4[j]];
	  }
	while (i < 3)
	  {
	    ret += '=';
	    ++i;
	  }
      }
    return (ret);
  }

  std::string Cipher::_base64Decode(std::uint8_t const *data,
                                    std::size_t const   len) const
  {
    std::function<bool(std::uint8_t const)> isBase64 =
        [](std::uint8_t const c) {
          return ((std::isalnum(c) || (c == '+') || (c == '/')));
        };
    std::string ret;
    std::size_t i = 0;
    std::array<std::uint8_t, 4> ref4;

    // Decode
    for (std::size_t ndx = 0, _len = len;
         _len && data[ndx] != '=' && isBase64(data[ndx]); ++ndx, --_len)
      {
	ref4[i] = data[ndx];
	++i;
	if (i == 4)
	  {
	    ref4[0] = static_cast<std::uint8_t>(
	        _b64Table.find(static_cast<char>(ref4[0])));
	    ref4[1] = static_cast<std::uint8_t>(
	        _b64Table.find(static_cast<char>(ref4[1])));
	    ref4[2] = static_cast<std::uint8_t>(
	        _b64Table.find(static_cast<char>(ref4[2])));
	    ref4[3] = static_cast<std::uint8_t>(
	        _b64Table.find(static_cast<char>(ref4[3])));
	    ret += static_cast<char>((ref4[0] << 2) + ((ref4[1] & 0x30) >> 4));
	    ret += static_cast<char>(((ref4[1] & 0x0F) << 4) +
	                             ((ref4[2] & 0x3C) >> 2));
	    ret += static_cast<char>(((ref4[2] & 0x03) << 6) + ref4[3]);
	    i = 0;
	  }
      }

    // Finish
    if (i)
      {
	std::array<std::uint8_t, 3> ref3;

	for (std::size_t j = i; j < 4; ++j)
	  {
	    ref4[j] = 0;
	  }

	ref4[0] = static_cast<std::uint8_t>(
	    _b64Table.find(static_cast<char>(ref4[0])));
	ref4[1] = static_cast<std::uint8_t>(
	    _b64Table.find(static_cast<char>(ref4[1])));
	ref4[2] = static_cast<std::uint8_t>(
	    _b64Table.find(static_cast<char>(ref4[2])));
	ref4[3] = static_cast<std::uint8_t>(
	    _b64Table.find(static_cast<char>(ref4[3])));

	ref3[0] = static_cast<std::uint8_t>((ref4[0] << 2) +
	                                    ((ref4[1] & 0x30) >> 4));
	ref3[1] = static_cast<std::uint8_t>(((ref4[1] & 0x0F) << 4) +
	                                    ((ref4[2] & 0x3C) >> 2));
	ref3[2] = static_cast<std::uint8_t>(((ref4[2] & 0x03) << 6) + ref4[3]);

	for (std::size_t j = 0; j < i - 1; ++j)
	  {
	    ret += static_cast<char>(ref3[j]);
	  }
      }
    return (ret);
  }
}
