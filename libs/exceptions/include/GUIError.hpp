#ifndef GUIERROR_HPP_
#define GUIERROR_HPP_

#include "AException.hpp"

// Disable clang warning for weak vtables
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

class GUIError : public indie::AException
{
public:
  explicit GUIError(std::string const &msg = "");
};

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !GUIERROR_HPP_
