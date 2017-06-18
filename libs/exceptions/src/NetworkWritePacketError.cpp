#include "exceptions_stdafx.hpp"
#include "NetworkWritePacketError.hpp"

NetworkWritePacketError::NetworkWritePacketError(std::string const &msg)
    : AException("NetworkWritePacketError: ", msg)
{
}
