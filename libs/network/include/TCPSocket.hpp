#ifndef TCPSOCKET_HPP_
#define TCPSOCKET_HPP_

#include "ASocket.hpp"

namespace network
{
  class TCPSocket : public ASocket
  {
  public:
    explicit TCPSocket(sock_t const sock);
    TCPSocket(std::uint16_t port, std::string const &host, bool ip,
              SocketType type);
    TCPSocket(std::uint16_t port, std::uint32_t maxClients, SocketType type);
    TCPSocket(TCPSocket &&);
    virtual ~TCPSocket();
    virtual bool send(void const *data, std::size_t len) const;
    virtual bool rec(void *buffer, std::size_t rlen, ssize_t *buffLen) const;
    virtual bool openConnection();

  private:
    bool sendBlocking(void const *data, std::size_t len) const;
    bool sendNonBlocking(void const *data, std::size_t len) const;
    bool recBlocking(void *buffer, std::size_t rlen, ssize_t *buffLen) const;
    bool recNonBlocking(void *buffer, std::size_t rlen,
                        ssize_t *buffLen) const;
  };
}

#endif // !TCPSOCKET_HPP_
