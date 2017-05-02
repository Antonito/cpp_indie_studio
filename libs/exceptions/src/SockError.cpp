#include "SockError.hpp"

namespace Network
{
  SockError::SockError(std::string const &msg)
      : AException("SocketError: ", msg)
  {
  }
}
