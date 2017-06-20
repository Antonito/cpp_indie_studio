#include "network_stdafx.hpp"
#if defined(__linux__) || defined(__APPLE__)
#include <fcntl.h>
#include <netdb.h>
#endif

#include <csignal>
#include <cassert>
#include <iostream>
#include "ASocket.hpp"
#include "SockError.hpp"

namespace network
{
// Make sure you have to init / deinit WSA
#if defined(_WIN32)
  std::uint32_t network::ASocket::m_nbSockets = 0;
  bool          network::ASocket::m_WSAInited = false;
#endif

  ASocket::ASocket(sock_t const socket)
      : m_socket(socket), m_port(0), m_host(""), m_ip(false), m_maxClients(0),
        m_curClients(0), m_addr{}, m_type()
  {
    nope::log::Log(Debug) << "Loading socket #" << m_socket;
#if defined(_WIN32)
    // Do we need to load the network DLL ?
    if (!m_nbSockets && !initWSA())
      {
	nope::log::Log(Error) << "Cannot load network DLL";
	throw network::SockError("Cannot load network DLL");
      }
    nope::log::Log(Debug) << "Adding socket " << m_nbSockets;
    ++m_nbSockets;
#endif
  }

  ASocket::ASocket(SocketType type)
      : m_socket(-1), m_port(0), m_host(""), m_ip(false), m_maxClients(0),
        m_curClients(0), m_addr{}, m_type(type)
  {
#if defined(__linux__) || (__APPLE__)
    // If we can, ignore SIGPIPE
    std::signal(SIGPIPE, SIG_IGN);
    nope::log::Log(Debug) << "Ignoring SIGPIPE";
#endif
#if defined(_WIN32)
    // Do we need to load the network DLL ?
    if (!m_nbSockets && !initWSA())
      {
	nope::log::Log(Error) << "Cannot load network DLL";
	throw network::SockError("Cannot load network DLL");
      }
    nope::log::Log(Debug) << "Adding socket " << m_nbSockets;
    ++m_nbSockets;
#endif
  }

  ASocket::ASocket(std::uint16_t port, std::string const &host,
                   SocketType type)
      : ASocket(type)
  {
    // cppcheck-suppress useInitializationList
    m_host = host;
    m_port = port;
  }

  ASocket::ASocket(std::uint16_t port, std::uint32_t maxClients,
                   SocketType type)
      : ASocket(type)
  {
    assert(maxClients);
    m_port = port;
    m_maxClients = maxClients;
  }

  ASocket::ASocket(ASocket const &other) : ASocket(other.m_type)
  {
    // cppcheck-suppress useInitializationList
    m_host = other.m_host;
    m_socket = other.m_socket;
    m_port = other.m_port;
    m_ip = other.m_ip;
    m_maxClients = other.m_maxClients;
    m_curClients = other.m_curClients;
    m_addr = other.m_addr;
  }

  ASocket::ASocket(ASocket &&other)
      : m_socket(other.m_socket), m_port(other.m_port), m_host(other.m_host),
        m_ip(other.m_ip), m_maxClients(other.m_maxClients),
        m_curClients(other.m_curClients), m_addr(other.m_addr),
        m_type(other.m_type)
  {
    other.m_socket = -1;
  }

  ASocket::~ASocket()
  {
    closeConnection();
#if defined(_WIN32)
    if (m_nbSockets)
      assert(m_nbSockets);
    --m_nbSockets;
    if (!m_nbSockets)
      {
	// It is the last socket
	nope::log::Log(Debug) << "Closing last socket";
	deinitWSA();
      }
#endif
  }

  // Close the socket
  bool ASocket::closeConnection()
  {
    if (m_socket > 0 && !closesocket(m_socket))
      {
	nope::log::Log(Debug) << "Closing socket #" << m_socket;
	m_socket = -1;
      }
    return (!isStarted());
  }

  ASocket &ASocket::operator=(ASocket const &other)
  {
    if (this != &other)
      {
	m_socket = other.m_socket;
	m_port = other.m_port;
	m_host = other.m_host;
	m_ip = other.m_ip;
	m_maxClients = other.m_maxClients;
	m_curClients = other.m_curClients;
	m_addr = other.m_addr;
	m_type = other.m_type;
      }
    return (*this);
  }

  bool ASocket::operator==(ASocket const &other) const
  {
    if (this != &other)
      {
	return (m_socket == other.m_socket);
      }
    return (true);
  }

  bool ASocket::isStarted() const
  {
    return (m_socket != -1);
  }

  sock_t ASocket::getSocket() const
  {
    return (m_socket);
  }

  std::uint16_t ASocket::getPort() const
  {
    return (m_port);
  }

  std::uint32_t ASocket::getMaxClients() const
  {
    return (m_maxClients);
  }

  std::uint32_t ASocket::getCurClients() const
  {
    return (m_curClients);
  }

  ASocket::SocketMode ASocket::getMode() const
  {
    if (m_maxClients != 0)
      {
	return (ASocket::SERVER);
      }
    return (ASocket::CLIENT);
  }

  ASocket::SocketType ASocket::getType() const
  {
    return (m_type);
  }

  sockaddr_in_t const &ASocket::getSockAddr() const
  {
    return (m_addr);
  }

  bool ASocket::connectToHost(std::int32_t const socktype,
                              std::int32_t const proto, bool shouldConnect)
  {
    addrinfo_t  hints = {};
    addrinfo_t *res = nullptr;
    bool        connected = false;
    SocketType  typeBackup;

    nope::log::Log(Debug) << "Connection to host";
    assert(m_socket == -1);
    if (m_ip)
      {
	nope::log::Log(Debug) << "Provided address is an IP";
	hints.ai_flags = AI_NUMERICHOST;
      }
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = socktype;
    hints.ai_protocol = proto;
    nope::log::Log(Debug) << "Processing address resolution";
    if (getaddrinfo(m_host.c_str(), std::to_string(m_port).c_str(), &hints,
                    &res) == 0)
      {
	// Loop over all the potential addresses
	for (addrinfo_t *ptr = res; ptr; ptr = ptr->ai_next)
	  {
	    std::int32_t ret = 0;

	    typeBackup = getType();
	    m_type = ASocket::BLOCKING;
	    try
	      {
		initSocket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	      }
	    catch (std::exception &e)
	      {
		std::cerr << e.what() << std::endl;
		break;
	      }

	    ret = 0;
	    if (shouldConnect)
	      {
#if defined(__linux__) || defined(__APPLE__)
		ret = connect(m_socket, ptr->ai_addr, ptr->ai_addrlen);
#elif defined(_WIN32)
		ret = connect(m_socket, ptr->ai_addr,
		              static_cast<std::int32_t>(ptr->ai_addrlen));
#endif
	      }
	    if (ret != -1)
	      {
		if (typeBackup == ASocket::NONBLOCKING)
		  {
		    m_type = ASocket::NONBLOCKING;
		    if (setSocketType() == false)
		      {
			throw network::SockError("Cannot set socket type");
		      }
		  }
		if (res->ai_addrlen <= sizeof(m_addr))
		  {
		    nope::log::Log(Debug) << "Updating sockaddr_in content";
		    std::memcpy(&m_addr, res->ai_addr, res->ai_addrlen);
		  }
		nope::log::Log(Debug) << "Found an address, connected !";
		connected = true;
		break;
	      }
	    closeConnection();
	  }
      }
    freeaddrinfo(res);
    return (connected);
  }

  void ASocket::initSocket(std::int32_t domain, std::int32_t type,
                           std::int32_t protocol)
  {
    char const enable = 1;

    nope::log::Log(Debug) << "Creating socket...";
    m_socket = ::socket(domain, type, protocol);
    if (m_socket == -1)
      {
	nope::log::Log(Error) << "Cannot create socket";
	throw network::SockError("Cannot create socket");
      }
    nope::log::Log(Debug) << "Created socket #" << m_socket;
    if (setSocketType() == false)
      {
	nope::log::Log(Error) << "Cannot set socket type";
	throw network::SockError("Cannot set socket type");
      }
    if (m_port != 0)
      {
	// Try to reuse the socket
	if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &enable,
	               sizeof(enable)) < 0)
	  {
	    if (errno != EINVAL)
	      {
		nope::log::Log(Error) << "Cannot set socket options";
		throw network::SockError("Cannot set socket options");
	      }
	  }
      }
    nope::log::Log(Debug) << "Socket created successfuly";
  }

  void ASocket::hostConnection()
  {
    nope::log::Log(Debug) << "Socket created successfuly";
    assert(m_socket != -1);
    m_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(m_socket, reinterpret_cast<sockaddr_t *>(&m_addr),
             sizeof(m_addr)) == -1)
      {
	throw network::SockError("Cannot bind to socket");
      }
    if (m_port == 0)
      {
	sockaddr_in_t newAddr = {};
	socklen_t     len = sizeof(sockaddr_in_t);

	// Get the port selected by the kernel
	if (getsockname(m_socket, reinterpret_cast<sockaddr_t *>(&newAddr),
	                &len) == -1)
	  {
	    throw network::SockError("Cannot get port selected by the kernel");
	  }
	m_port = ntohs(newAddr.sin_port);
      }
  }

  // Set the socket to blocking or non-blocking state
  bool ASocket::setSocketType() const
  {
    bool ret;

    assert(isStarted());
#if defined(_WIN32)
    unsigned long lock = !(m_type == ASocket::BLOCKING);
    ret = ioctlsocket(m_socket, FIONBIO, &lock) == 0;
#else
    std::int32_t flags;

#if defined(O_NONBLOCK)
    flags = fcntl(m_socket, F_GETFL, 0);
    ret = false;
    if (flags >= 0)
      {
	flags = (m_type == ASocket::BLOCKING) ? (flags & ~O_NONBLOCK)
	                                      : (flags | O_NONBLOCK);
	ret = fcntl(m_socket, F_SETFL, flags) == 0;
      }
#else
    flags = 1;
    ret = ioctl(m_socket, FIOBIO, &flags) == 0;
#endif

#endif
    return (ret);
  }

#if defined(_WIN32)
  bool ASocket::initWSA() const
  {
    WSADATA wsa;

    assert(m_WSAInited == false);
    if (WSAStartup(MAKEWORD(2, 2), &wsa) < 0)
      {
	// Initialization failed
	return (false);
      }
    m_WSAInited = true;
    return (true);
  }

  void ASocket::deinitWSA() const
  {
    assert(m_WSAInited == true);
    WSACleanup();
    m_WSAInited = false;
  }
#endif
}
