#include "exceptions_stdafx.hpp"
#include "GUIError.hpp"

GUIError::GUIError(std::string const &msg) : AException("GUIError: ", msg)
{
}
