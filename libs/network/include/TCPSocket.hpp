#ifndef TCPSOCKET_HPP_
#define TCPSOCKET_HPP_

#include "ASocket.hpp"

namespace Network
{
  class TCPSocket : public ASocket
  {
  public:
    TCPSocket(uint16_t port, std::string const &host, bool ip,
              SocketType type);
    TCPSocket(uint16_t port, uint32_t maxClients, SocketType type);
    virtual ~TCPSocket();
    virtual bool send(void const *data, size_t len) const;
    virtual bool rec(void **buffer, size_t rlen, ssize_t *buffLen) const;
    virtual bool openConnection();

  protected:
    virtual void hostConnection();

  private:
    bool sendBlocking(void const *data, size_t len) const;
    bool sendNonBlocking(void const *data, size_t len) const;
    bool recBlocking(void **buffer, size_t rlen, ssize_t *buffLen) const;
    bool recNonBlocking(void **buffer, size_t rlen, ssize_t *buffLen) const;
  };
}

#endif // !TCPSOCKET_HPP_
