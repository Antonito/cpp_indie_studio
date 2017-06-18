#include "exceptions_stdafx.hpp"
#include "NetworkInvalidMapError.hpp"

NetworkInvalidMapError::NetworkInvalidMapError(std::string const &msg)
    : AException("NetworkInvalidMapError: ", msg)
{
}
