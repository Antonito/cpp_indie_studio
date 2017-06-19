#include "network_stdafx.hpp"
#include <cerrno>
#include <cassert>
#include "TCPSocket.hpp"
#include "SockError.hpp"

namespace network
{
  TCPSocket::TCPSocket(sock_t const sock) : ASocket(sock)
  {
  }

  TCPSocket::TCPSocket(std::uint16_t port, std::string const &host, bool ip,
                       SocketType type)
      : ASocket(port, host, type)
  {
    m_ip = ip;
  }

  TCPSocket::TCPSocket(std::uint16_t port, std::uint32_t maxClients,
                       SocketType type)
      : ASocket(port, maxClients, type)
  {
  }

  TCPSocket::TCPSocket(TCPSocket &&other) : ASocket(std::move(other))
  {
  }

  TCPSocket::~TCPSocket()
  {
  }

  bool TCPSocket::openConnection()
  {
    bool ret;

    nope::log::Log(Debug) << "Opening TCP connection";
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
	    if (listen(m_socket, static_cast<std::int32_t>(m_maxClients)) ==
	        -1)
	      {
		throw network::SockError("Cannot listen on socket");
	      }
	  }
	catch (std::exception &e)
	  {
	    nope::log::Log(Error) << e.what();
	    ret = false;
	  }
      }
    else
      {
	ret = connectToHost(SOCK_STREAM, IPPROTO_TCP, true);
      }
    if (ret == false)
      {
	if (m_socket > 0)
	  closesocket(m_socket);
	m_socket = -1;
      }
    return (ret && isStarted());
  }

  bool TCPSocket::sendBlocking(void const *data, std::size_t len) const
  {
    ssize_t     ret;
    std::size_t off = 0;

    assert(getType() == ASocket::BLOCKING);
    do
      {
#if defined(__linux__) || defined(__APPLE__)
	ret = ::send(m_socket, static_cast<char const *>(data) + off,
	             len - off, 0);
#elif defined(_WIN32)
	ret = ::send(m_socket, static_cast<char const *>(data) + off,
	             static_cast<std::int32_t>(len - off), 0);
#endif
	if (ret <= 0)
	  {
	    return (!ret);
	  }
	off += static_cast<std::size_t>(ret);
      }
    while (off != len);
    nope::log::Log(Debug) << "Sent " << ret << "/" << len;
    return (true);
  }

  bool TCPSocket::sendNonBlocking(void const *data, std::size_t len) const
  {
    std::uint8_t const *msg = static_cast<std::uint8_t const *>(data);
    std::size_t         off = 0;
    bool                success = true;

    assert(getType() == ASocket::NONBLOCKING);
    for (;;)
      {
	ssize_t ret;

#if defined(__linux__) || defined(__APPLE__)
	ret = ::send(m_socket, reinterpret_cast<char const *>(msg + off),
	             len - off, 0);
#elif defined(_WIN32)
	ret = ::send(m_socket, reinterpret_cast<char const *>(msg + off),
	             static_cast<std::int32_t>(len - off), 0);
#endif
	if (ret == -1 || static_cast<std::size_t>(ret) == len - off)
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

  bool TCPSocket::send(void const *data, std::size_t len) const
  {
    assert(isStarted());
    if (getType() == ASocket::BLOCKING)
      {
	return (sendBlocking(data, len));
      }
    return (sendNonBlocking(data, len));
  }

  bool TCPSocket::recBlocking(void *buffer, std::size_t rlen,
                              ssize_t *buffLen) const
  {
    assert(getType() == ASocket::BLOCKING);
    std::size_t off = 0;

    // TODO: Remove useless debug log, do while should be one level above (use
    // header informations)
    nope::log::Log(Debug) << "recblocking Rlen -> " << rlen;
    do
      {
#if defined(__linux__) || defined(__APPLE__)
	*buffLen =
	    ::recv(m_socket, static_cast<char *>(buffer) + off, rlen - off, 0);
#elif defined(_WIN32)
	*buffLen = ::recv(m_socket, static_cast<char *>(buffer) + off,
	                  static_cast<std::int32_t>(rlen - off), 0);
#endif
	nope::log::Log(Debug) << "recblocking BuffLen -> " << *buffLen;
	if (*buffLen <= 0)
	  {
	    nope::log::Log(Debug) << "recBlocking -> <= 0 [TCP]";
	    return (!*buffLen);
	  }
	off += static_cast<std::size_t>(*buffLen);
      }
    while (off != rlen);
    *buffLen = static_cast<ssize_t>(off);
    nope::log::Log(Debug) << "Read " << *buffLen << "/" << rlen;
    return (true);
  }

  bool TCPSocket::recNonBlocking(void *buffer, std::size_t rlen,
                                 ssize_t *buffLen) const
  {
    std::uint8_t *buf;
    bool          success = true;

    assert(getType() == ASocket::NONBLOCKING);
    buf = static_cast<std::uint8_t *>(buffer);
    *buffLen = 0;
    for (;;)
      {
	ssize_t ret;

#if defined(__linux__) || defined(__APPLE__)
	ret = ::recv(m_socket, reinterpret_cast<char *>(buf + *buffLen),
	             rlen - static_cast<std::size_t>(*buffLen), 0);
#elif defined(_WIN32)
	ret = ::recv(m_socket, reinterpret_cast<char *>(buf + *buffLen),
	             static_cast<std::int32_t>(rlen - *buffLen), 0);
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
	    nope::log::Log(Debug) << "recNonBlocking -> 0 [TCP]";
	    *buffLen = 0;
	    break;
	  }
	if (static_cast<std::size_t>(*buffLen + ret) >= rlen)
	  {
	    success = !(static_cast<std::size_t>(*buffLen + ret) > rlen);
	    break;
	  }
	*buffLen += ret;
      }
    return (success);
  }

  bool TCPSocket::rec(void *buffer, std::size_t rlen, ssize_t *buffLen) const
  {
    assert(isStarted());
    if (getType() == ASocket::BLOCKING)
      {
	return (recBlocking(buffer, rlen, buffLen));
      }
    return (recNonBlocking(buffer, rlen, buffLen));
  }
}
