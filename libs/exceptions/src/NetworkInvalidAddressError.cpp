#include "exceptions_stdafx.hpp"
#include "NetworkInvalidAddressError.hpp"

NetworkInvalidAddressError::NetworkInvalidAddressError(std::string const &msg)
    : AException("NetworkInvalidAddressError: ", msg)
{
}
