#include "exceptions_stdafx.hpp"
#include "NetworkReadPacketError.hpp"

NetworkReadPacketError::NetworkReadPacketError(std::string const &msg)
    : AException("NetworkReadPacketError: ", msg)
{
}
