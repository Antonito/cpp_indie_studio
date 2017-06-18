#ifndef MAPERROR_HPP_
#define MAPERROR_HPP_

#include "AException.hpp"

// Disable clang warning for weak vtables
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

class MapError : public indie::AException
{
public:
  explicit MapError(std::string const &msg = "");
};

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !MAPERROR_HPP_
