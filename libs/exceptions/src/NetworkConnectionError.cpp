#include "exceptions_stdafx.hpp"
#include "NetworkConnectionError.hpp"

NetworkConnectionError::NetworkConnectionError(std::string const &msg)
    : AException("NetworkConnectionError: ", msg)
{
}
