#ifndef ISERVER_HPP_
#define ISERVER_HPP_

#include "IClient.hpp"

namespace Network
{
  class IServer
  {
  public:
    virtual ~IServer(){};
    virtual bool run() = 0;
    virtual void stop() = 0;
    virtual bool addClient() = 0;
    virtual bool removeClient(IClient &) = 0;
  };
}

#endif // !ISERVER_HPP_
