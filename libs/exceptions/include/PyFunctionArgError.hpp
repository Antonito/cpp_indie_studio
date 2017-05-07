//
// Created by brout_m on 05/05/17.
//

#ifndef PYFUNCTIONARGERROR_HPP
#define PYFUNCTIONARGERROR_HPP

#include "AException.hpp"

// Disable clang warning for weak vtables
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

namespace pythonpp
{
  class PyFunctionArgError : public indie::AException
  {
  public:
    explicit PyFunctionArgError(std::string const &msg = "");
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // PYFUNCTIONARGERROR_HPP
