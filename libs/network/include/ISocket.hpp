#ifndef ISOCKET_HPP_
#define ISOCKET_HPP_

#include "GenNetwork.hpp"

namespace Network
{
  class ISocket
  {
  public:
    virtual ~ISocket()
    {
    }
    virtual bool send(void const *data, size_t len) const = 0;
    virtual bool rec(void **buffer, size_t rlen, ssize_t *buffLen) const = 0;
    virtual bool openConnection() = 0;
    virtual bool closeConnection() = 0;

  protected:
    virtual bool connectToHost() = 0;
    virtual void hostConnection() = 0;
  };
}

#endif // !ISOCKET_HPP_
