#ifndef NETWORKCONNECTIONERROR_HPP_
#define NETWORKCONNECTIONERROR_HPP_

#include "AException.hpp"

// Disable clang warning for weak vtables
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

class NetworkConnectionError : public indie::AException
{
public:
  explicit NetworkConnectionError(std::string const &msg = "");
};

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !NETWORKCONNECTIONERROR_HPP_
