#ifndef ASOCKET_HPP_
#define ASOCKET_HPP_

#include <string>
#include <array>
#include "ISocket.hpp"

// TODO: Add IPv4 / IPV6 selection, SSL / TLS
namespace Network
{
  class ASocket : public ISocket
  {
  public:
    enum SocketMode
    {
      SERVER,
      CLIENT
    };
    enum SocketType
    {
      BLOCKING,
      NONBLOCKING
    };
    virtual ~ASocket();
    virtual bool closeConnection();

    bool       isStarted() const;
    sock_t     getSocket() const;
    uint16_t   getPort() const;
    uint32_t   getMaxClients() const;
    uint32_t   getCurClients() const;
    SocketMode getMode() const;
    SocketType getType() const;

  protected:
    ASocket(uint16_t port, std::string const &host,
            SocketType type = ASocket::BLOCKING);
    ASocket(uint16_t port, uint32_t maxClients,
            SocketType type = ASocket::BLOCKING);
    ASocket(ASocket const &other);
    ASocket &operator=(ASocket const &);

    virtual bool connectToHost();
    void initSocket(int domain, int type, int protocol);
    bool setSocketType() const;

    sock_t        m_socket;
    uint16_t      m_port;
    std::string   m_host;
    bool          m_ip;
    uint32_t      m_maxClients;
    uint32_t      m_curClients;
    sockaddr_in_t m_addr;
    SocketType    m_type;

  private:
    ASocket(SocketType type);

// Init network DLL
#if defined(_WIN32)
    static uint32_t m_nbSockets;
    static bool     m_WSAInited;
    bool            initWSA() const;
    void            deinitWSA() const;
#endif

    std::array<std::uint8_t, 2> _padding;
  };
}

#endif // !ASOCKET_HPP_
