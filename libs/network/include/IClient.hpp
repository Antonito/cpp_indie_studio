#ifndef ICLIENT_HPP_
#define ICLIENT_HPP_

#include "IPacket.hpp"

// Disable clang warning for weak vtables
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

namespace network
{
  class IClient
  {
  public:
    enum ClientAction
    {
      SUCCESS,
      FAILURE,
      DISCONNECT
    };

    virtual ~IClient()
    {
    }
    virtual bool                           disconnect() = 0;
    virtual network::IClient::ClientAction write(IPacket const &) = 0;
    virtual network::IClient::ClientAction read(IPacket &) = 0;
    virtual bool                           hasTimedOut() const = 0;
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !ICLIENT_HPP_
