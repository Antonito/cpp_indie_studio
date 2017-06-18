//
// Created by brout_m on 05/05/17.
//

#include "exceptions_stdafx.hpp"
#include "PyFunctionArgError.hpp"

pythonpp::PyFunctionArgError::PyFunctionArgError(const std::string &msg)
    : AException("PyFunctionArgError: ", msg)
{
}
