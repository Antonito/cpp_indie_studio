#ifndef NETWORKWRITEPACKETERROR_HPP_
#define NETWORKWRITEPACKETERROR_HPP_

#include "AException.hpp"

// Disable clang warning for weak vtables
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

class NetworkWritePacketError : public indie::AException
{
public:
  explicit NetworkWritePacketError(std::string const &msg = "");
};

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !NETWORKWRITEPACKETERROR_HPP_
