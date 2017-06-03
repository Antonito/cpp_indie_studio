#ifndef REQUEST_TOKEN_HPP_
#define REQUEST_TOKEN_HPP_

#include <cstdint>
#include <array>

// Used to communicate between gameServer and gameClientServer
struct TokenCom
{
  TokenCom() : treated(0), tokenData()
  {
  }

  int32_t treated;
  std::array<char, 40> tokenData;
};

#endif // !REQUEST_TOKEN_HPP_
