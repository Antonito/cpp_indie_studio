//
// Created by brout_m on 03/05/17.
//

#ifndef PYINITIALIZATIONERROR_HPP
#define PYINITIALIZATIONERROR_HPP

#include "AException.hpp"

// Disable clang warning for weak vtables
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

namespace pythonpp
{
  class PyInitializationError : public indie::AException
  {
  public:
    explicit PyInitializationError(std::string const &msg = "");
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // PYINITIALIZATIONERROR_HPP
