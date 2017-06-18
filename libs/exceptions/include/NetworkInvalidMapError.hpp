#ifndef NETWORKINVALIDMAPERROR_HPP_
#define NETWORKINVALIDMAPERROR_HPP_

#include "AException.hpp"

// Disable clang warning for weak vtables
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

class NetworkInvalidMapError : public indie::AException
{
public:
  explicit NetworkInvalidMapError(std::string const &msg = "");
};

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !NETWORKINVALIDMAPERROR_HPP_
