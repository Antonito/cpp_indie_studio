//
// Created by brout_m on 04/05/17.
//

#include "exceptions_stdafx.hpp"
#include "PyFunctionInitializationError.hpp"

pythonpp::PyFunctionInitializationError::PyFunctionInitializationError(
    std::string const &msg)
    : AException("PythonFunctionInitializationError: ", msg)
{
}
