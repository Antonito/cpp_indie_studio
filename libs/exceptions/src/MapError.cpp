#include "exceptions_stdafx.hpp"
#include "MapError.hpp"

MapError::MapError(std::string const &msg) : AException("MapError: ", msg)
{
}
