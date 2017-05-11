#ifndef SOCKERROR_HPP_
#define SOCKERROR_HPP_

#include "AException.hpp"

// Disable clang warning for weak vtables
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

namespace network
{
  class SockError : public indie::AException
  {
  public:
    explicit SockError(std::string const &msg = "");
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !SOCKERROR_HPP_
