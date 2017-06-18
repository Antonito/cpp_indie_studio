#ifndef NETWORKINVALIDADDRESSERROR_HPP_
#define NETWORKINVALIDADDRESSERROR_HPP_

#include "AException.hpp"

// Disable clang warning for weak vtables
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

class NetworkInvalidAddressError : public indie::AException
{
public:
  explicit NetworkInvalidAddressError(std::string const &msg = "");
};

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !NETWORKINVALIDADDRESSERROR_HPP_
