#ifndef NETWORKREADPACKETERROR_HPP_
#define NETWORKREADPACKETERROR_HPP_

#include "AException.hpp"

// Disable clang warning for weak vtables
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

class NetworkReadPacketError : public indie::AException
{
public:
  explicit NetworkReadPacketError(std::string const &msg = "");
};

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !NETWORKREADPACKETERROR_HPP_
