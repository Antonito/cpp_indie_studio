#include "network_stdafx.hpp"

namespace network
{
  UDPSocket::UDPSocket(sock_t const sock) : ASocket(sock)
  {
  }

  UDPSocket::UDPSocket(std::uint16_t port, std::string const &host, bool ip,
                       ASocket::SocketType type)
      : ASocket(port, host, type)
  {
    m_ip = ip;
  }

  UDPSocket::UDPSocket(std::uint16_t port, std::uint32_t maxClients,
                       ASocket::SocketType type)
      : ASocket(port, maxClients, type)
  {
  }

  UDPSocket::UDPSocket(UDPSocket &&other) : ASocket(std::move(other))
  {
  }

  UDPSocket::~UDPSocket()
  {
  }

  bool UDPSocket::send(void const *, std::size_t) const
  {
    // Not implemented
    return (false);
  }

  bool UDPSocket::send(void const *data, std::size_t len,
                       sockaddr_t const *dest, socklen_t destLen) const
  {
    ssize_t ret;

    assert(isStarted());
    do
      {
	ret = sendto(m_socket, data, len, 0, dest, destLen);
      }
    while (ret == -1 && errno == EINTR);
    return (ret != -1);
  }

  bool UDPSocket::rec(void *, std::size_t, ssize_t *) const
  {
    // Not implemented
    return (false);
  }

  bool UDPSocket::rec(void *buffer, std::size_t rlen, sockaddr_t *addr,
                      socklen_t *addrLen) const
  {
    ssize_t ret;

    assert(isStarted());
    do
      {
	ret = recvfrom(m_socket, buffer, rlen, 0, addr, addrLen);
      }
    while (ret == -1 && errno == EINTR);
    return (ret != -1);
  }

  bool UDPSocket::openConnection()
  {
    bool ret;

    nope::log::Log(Debug) << "Opening UDP connection [ " << m_port << " ]";
    assert(!isStarted());
    if (getMode() == ASocket::SERVER)
      {
	nope::log::Log(Debug) << "Hosting connection";
	ret = true;
	try
	  {
	    initSocket(AF_INET, SOCK_DGRAM, 0);
	    nope::log::Log(Debug) << "Socket init'd.";
	    m_addr.sin_port = htons(m_port);
	    m_addr.sin_family = AF_INET;
	    hostConnection();
	  }
	catch (std::exception &e)
	  {
	    nope::log::Log(Error) << e.what();
	    ret = false;
	  }
      }
    else
      {
	ret = true;
	try
	  {
	    initSocket(AF_INET, SOCK_DGRAM, 0);
	    m_addr.sin_port = htons(m_port);
	    m_addr.sin_family = AF_INET;
	  }
	catch (std::exception &e)
	  {
	    nope::log::Log(Error) << e.what();
	    ret = false;
	  }
	if (ret)
	  {
	    if (m_ip)
	      {
		nope::log::Log(Debug) << "Host is an IP";
		m_addr.sin_addr.s_addr = inet_addr(m_host.c_str());
	      }
	    else
	      {
		struct hostent *hostinfo;

		nope::log::Log(Debug) << "Host is not an IP";
		hostinfo = gethostbyname(m_host.c_str());
		if (hostinfo == NULL)
		  {
		    nope::log::Log(Error) << "Unknown host " << m_host.c_str();
		    ret = false;
		  }
		else
		  {
		    m_addr.sin_addr =
		        *reinterpret_cast<in_addr const *>(hostinfo->h_addr);
		  }
	      }
	  }
      }
    if (ret == false)
      {
	if (m_socket > 0)
	  closesocket(m_socket);
	m_socket = -1;
      }
    return (ret && isStarted());
  }
}
