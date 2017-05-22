//
// Created by brout_m on 05/05/17.
//

#ifndef PYFUNCTIONRETURNERROR_HPP
#define PYFUNCTIONRETURNERROR_HPP

#include "AException.hpp"

// Disable clang warning for weak vtables
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

namespace pythonpp
{
  class PyFunctionReturnError : public indie::AException
  {
  public:
    explicit PyFunctionReturnError(std::string const &msg = "");
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // PYFUNCTIONRETURNERROR_HPP
