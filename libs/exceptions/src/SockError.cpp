#include "exceptions_stdafx.hpp"
#include "SockError.hpp"

namespace network
{
  SockError::SockError(std::string const &msg)
      : AException("SocketError: ", msg)
  {
  }
}
