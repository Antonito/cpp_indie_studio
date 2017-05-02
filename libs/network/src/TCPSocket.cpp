#include <cerrno>
#include <cassert>
#include "TCPSocket.hpp"
#include "SockError.hpp"

namespace Network
{
  TCPSocket::TCPSocket(uint16_t port, std::string const &host, bool ip,
                       SocketType type)
      : ASocket(port, host, type)
  {
    m_ip = ip;
  }

  TCPSocket::TCPSocket(uint16_t port, uint32_t maxClients, SocketType type)
      : ASocket(port, maxClients, type)
  {
  }

  TCPSocket::~TCPSocket()
  {
  }

  bool TCPSocket::openConnection()
  {
    bool ret;

    assert(!isStarted());
    if (getMode() == ASocket::SERVER)
      {
	ret = true;
	try
	  {
	    initSocket(AF_INET, SOCK_STREAM, 0);
	    m_addr.sin_port = htons(m_port);
	    m_addr.sin_family = AF_INET;
	    hostConnection();
	  }
	catch (std::exception &)
	  {
	    ret = false;
	  }
      }
    else
      {
	ret = connectToHost();
      }
    if (ret == false)
      {
	if (m_socket > 0)
	  closesocket(m_socket);
	m_socket = -1;
      }
    return (ret && isStarted());
  }

  bool TCPSocket::sendBlocking(void const *data, size_t len) const
  {
    ssize_t ret;

    assert(getType() == ASocket::BLOCKING);
#if defined(__linux__) || defined(__APPLE__)
    ret = ::send(m_socket, static_cast<char const *>(data), len, 0);
#elif defined(_WIN32)
    ret = ::send(m_socket, static_cast<char const *>(data),
                 static_cast<int>(len), 0);
#endif
    if (ret < 0)
      {
	return (false);
      }
    return (true);
  }

  bool TCPSocket::sendNonBlocking(void const *data, size_t len) const
  {
    uint8_t const *msg = static_cast<uint8_t const *>(data);
    size_t         off = 0;
    bool           success = true;

    assert(getType() == ASocket::NONBLOCKING);
    for (;;)
      {
	ssize_t ret;

#if defined(__linux__) || defined(__APPLE__)
	ret = ::send(m_socket, reinterpret_cast<char const *>(msg + off),
	             len - off, 0);
#elif defined(_WIN32)
	ret = ::send(m_socket, reinterpret_cast<char const *>(msg + off),
	             static_cast<int>(len - off), 0);
#endif
	if (ret == -1 || static_cast<size_t>(ret) == len - off)
	  {
	    if (ret == -1 && errno != EWOULDBLOCK && errno != EAGAIN)
	      {
		success = false;
	      }
	    break;
	  }
	off += static_cast<std::size_t>(ret);
      }
    return (success);
  }

  bool TCPSocket::send(void const *data, size_t len) const
  {
    assert(isStarted());
    if (getType() == ASocket::BLOCKING)
      {
	return (sendBlocking(data, len));
      }
    return (sendNonBlocking(data, len));
  }

  bool TCPSocket::recBlocking(void **buffer, size_t rlen,
                              ssize_t *buffLen) const
  {
    assert(getType() == ASocket::BLOCKING);
    *buffer = new uint8_t[rlen];
#if defined(__linux__) || defined(__APPLE__)
    *buffLen = ::recv(m_socket, static_cast<char *>(*buffer), rlen, 0);
#elif defined(_WIN32)
    *buffLen = ::recv(m_socket, static_cast<char *>(*buffer),
                      static_cast<int>(rlen), 0);
#endif
    if (*buffLen < 0)
      {
	*buffLen = 0;
	return (false);
      }
    return (true);
  }

  bool TCPSocket::recNonBlocking(void **buffer, size_t rlen,
                                 ssize_t *buffLen) const
  {
    uint8_t *buf;
    bool     success = true;

    assert(getType() == ASocket::NONBLOCKING);
    *buffer = new uint8_t[rlen];
    buf = static_cast<uint8_t *>(*buffer);
    *buffLen = 0;
    for (;;)
      {
	ssize_t ret;

#if defined(__linux__) || defined(__APPLE__)
	ret = ::recv(m_socket, reinterpret_cast<char *>(buf + *buffLen),
	             rlen - static_cast<std::size_t>(*buffLen), 0);
#elif defined(_WIN32)
	ret = ::recv(m_socket, reinterpret_cast<char *>(buf + *buffLen),
	             static_cast<int>(rlen - *buffLen), 0);
#endif
	if (ret == -1)
	  {
#if EWOULDBLOCK == EAGAIN
	    if (errno != EWOULDBLOCK)
#else
	    if (errno != EWOULDBLOCK && errno != EAGAIN)
#endif
	      {
		success = false;
	      }
	    break;
	  }
	else if (ret == 0)
	  {
	    *buffLen = 0;
	    break;
	  }
	if (static_cast<size_t>(*buffLen + ret) >= rlen)
	  {
	    success = !(static_cast<size_t>(*buffLen + ret) > rlen);
	    break;
	  }
	*buffLen += ret;
      }
    return (success);
  }

  bool TCPSocket::rec(void **buffer, size_t rlen, ssize_t *buffLen) const
  {
    assert(isStarted());
    if (getType() == ASocket::BLOCKING)
      {
	return (recBlocking(buffer, rlen, buffLen));
      }
    return (recNonBlocking(buffer, rlen, buffLen));
  }

  void TCPSocket::hostConnection()
  {
    assert(m_socket != -1);
    m_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(m_socket, reinterpret_cast<sockaddr_t *>(&m_addr),
             sizeof(m_addr)) == -1)
      {
	throw Network::SockError("Cannot bind to socket");
      }
    if (m_port == 0)
      {
	sockaddr_in_t newAddr = {};
	socklen_t     len = sizeof(sockaddr_in_t);

	// Get the port selected by the kernel
	if (getsockname(m_socket, reinterpret_cast<sockaddr_t *>(&newAddr),
	                &len) == -1)
	  {
	    throw Network::SockError("Cannot get port selected by the kernel");
	  }
	m_port = ntohs(newAddr.sin_port);
      }
    if (listen(m_socket, static_cast<std::int32_t>(m_maxClients)) == -1)
      {
	throw Network::SockError("Cannot listen on socket");
      }
  }
}
