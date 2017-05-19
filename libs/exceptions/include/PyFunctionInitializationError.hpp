//
// Created by brout_m on 04/05/17.
//

#ifndef PYFUNCTIONINITIALIZATIONERROR_HPP
#define PYFUNCTIONINITIALIZATIONERROR_HPP

#include "AException.hpp"

// Disable clang warning for weak vtables
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

namespace pythonpp
{
  class PyFunctionInitializationError : public indie::AException
  {
  public:
    explicit PyFunctionInitializationError(std::string const &msg = "");
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // PYFUNCTIONINITIALIZATIONERROR_HPP
