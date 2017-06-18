#include "exceptions_stdafx.hpp"
#include "IOError.hpp"

IOError::IOError(std::string const &msg) : AException("IOError: ", msg)
{
}
