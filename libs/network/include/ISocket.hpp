#ifndef ISOCKET_HPP_
#define ISOCKET_HPP_

#include "GenNetwork.hpp"

// Disable clang warning for weak vtables
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

namespace network
{
  class ISocket
  {
  public:
    virtual ~ISocket()
    {
    }
    virtual bool send(void const *data, std::size_t len) const = 0;
    virtual bool rec(void *buffer, std::size_t rlen,
                     ssize_t *buffLen) const = 0;
    virtual bool openConnection() = 0;
    virtual bool closeConnection() = 0;

  protected:
    virtual bool connectToHost(std::int32_t const socktype,
                               std::int32_t const proto,
                               bool               shouldConnect) = 0;
    virtual void hostConnection() = 0;
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !ISOCKET_HPP_
