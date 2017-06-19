#ifndef ASOCKET_HPP_
#define ASOCKET_HPP_

#include <cstring>
#include <string>
#include <cstring>
#include "ISocket.hpp"

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

// TODO: Add IPv4 / IPV6 selection, SSL / TLS
namespace network
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

    ASocket(ASocket const &other);
    ASocket &operator=(ASocket const &);
    ASocket(ASocket &&);

    virtual ~ASocket();
    virtual bool closeConnection();

    bool          isStarted() const;
    sock_t        getSocket() const;
    std::uint16_t getPort() const;
    std::uint32_t getMaxClients() const;
    std::uint32_t getCurClients() const;
    SocketMode    getMode() const;
    SocketType    getType() const;

    sockaddr_in_t const &getSockAddr() const;

    bool operator==(ASocket const &other) const;

  protected:
    explicit ASocket(sock_t const socket);
    ASocket(std::uint16_t port, std::string const &host,
            SocketType type = ASocket::BLOCKING);
    ASocket(std::uint16_t port, std::uint32_t maxClients,
            SocketType type = ASocket::BLOCKING);

    virtual bool connectToHost(std::int32_t const socktype,
                               std::int32_t const proto, bool shouldConnect);
    virtual void hostConnection();
    void initSocket(std::int32_t domain, std::int32_t type,
                    std::int32_t protocol);
    bool setSocketType() const;

    sock_t        m_socket;
    std::uint16_t m_port;
    std::string   m_host;
    bool          m_ip;
    std::uint32_t m_maxClients;
    std::uint32_t m_curClients;
    sockaddr_in_t m_addr;
    SocketType    m_type;

  private:
    explicit ASocket(SocketType type);

// Init network DLL
#if defined(_WIN32)
    static std::uint32_t m_nbSockets;
    static bool          m_WSAInited;
    bool                 initWSA() const;
    void                 deinitWSA() const;
#endif
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !ASOCKET_HPP_
