#include "exceptions_stdafx.hpp"
#include "NetworkInvalidPacketError.hpp"

NetworkInvalidPacketError::NetworkInvalidPacketError(std::string const &msg)
    : AException("NetworkInvalidPacketError: ", msg)
{
}
