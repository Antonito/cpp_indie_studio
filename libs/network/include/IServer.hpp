#ifndef ISERVER_HPP_
#define ISERVER_HPP_

#include "IClient.hpp"

// Disable clang warning for weak vtables
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

namespace network
{
  class IServer
  {
  public:
    virtual ~IServer()
    {
    }
    virtual bool run() = 0;
    virtual void stop() = 0;
    virtual bool addClient() = 0;
    virtual bool removeClient(IClient &) = 0;
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !ISERVER_HPP_
