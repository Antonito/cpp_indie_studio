//
// Created by brout_m on 05/05/17.
//
#include "exceptions_stdafx.hpp"
#include "PyFunctionReturnError.hpp"

pythonpp::PyFunctionReturnError::PyFunctionReturnError(const std::string &msg)
    : AException("PyFunctionReturnError: ", msg)
{
}
