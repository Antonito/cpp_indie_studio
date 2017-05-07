//
// Created by brout_m on 04/05/17.
//

#include "PyFunctionInitializationError.hpp"

pythonpp::PyFunctionInitializationError::PyFunctionInitializationError(
    std::string const &msg)
    : AException("PythonFunctionInitializationError: ", msg)
{
}
