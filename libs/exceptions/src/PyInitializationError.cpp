//
// Created by brout_m on 03/05/17.
//
#include "exceptions_stdafx.hpp"
#include "PyInitializationError.hpp"

pythonpp::PyInitializationError::PyInitializationError(const std::string &msg)
    : AException("PythonInitializationError: ", msg)
{
}
