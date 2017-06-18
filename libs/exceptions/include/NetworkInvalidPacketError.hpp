#ifndef NETWORKINVALIDPACKETERROR_HPP_
#define NETWORKINVALIDPACKETERROR_HPP_

#include "AException.hpp"

// Disable clang warning for weak vtables
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

class NetworkInvalidPacketError : public indie::AException
{
public:
  explicit NetworkInvalidPacketError(std::string const &msg = "");
};

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !NETWORKINVALIDPACKETERROR_HPP_
