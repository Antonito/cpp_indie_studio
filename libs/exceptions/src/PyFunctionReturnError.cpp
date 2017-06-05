//
// Created by brout_m on 05/05/17.
//

#include "PyFunctionReturnError.hpp"

pythonpp::PyFunctionReturnError::PyFunctionReturnError(const std::string &msg)
    : AException("PyFunctionReturnError: ", msg)
{
}
