#ifndef REQUEST_TOKEN_HPP_
#define REQUEST_TOKEN_HPP_

#include <cstdint>
#include <array>

// Used to communicate between gameServer and gameClientServer
struct TokenCom
{
  TokenCom() : ip(), port(0), treated(0), tokenData()
  {
  }

  std::array<char, INET6_ADDRSTRLEN_INDIE> ip;
  std::uint16_t port;
  std::int32_t  treated;
  std::array<char, 40> tokenData;
};

#endif // !REQUEST_TOKEN_HPP_
