#include "SockError.hpp"

namespace network
{
  SockError::SockError(std::string const &msg)
      : AException("SocketError: ", msg)
  {
  }
}
