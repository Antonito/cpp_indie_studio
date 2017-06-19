#ifndef GENNETWORK_HPP_
#define GENNETWORK_HPP_

#include <cstddef>
#include <cstdint>

#if defined(__linux__) || defined(__APPLE__)

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#define closesocket(s) close(s)

// Uniform type declarations
typedef std::int32_t       sock_t;
typedef struct sockaddr_in sockaddr_in_t;
typedef struct sockaddr    sockaddr_t;
typedef struct in_addr     _in_addr_t;
typedef struct addrinfo    addrinfo_t;

static_assert(INET6_ADDRSTRLEN == 46, "INET6_ADDRSTRLEN changed.");

#elif defined(_WIN32)

// Prevent inclusion of winsock.h in windows.h
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#endif

#include <windows.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib") // Link with ws2_32.lib

// Uniform type declarations
typedef SOCKET          sock_t;
typedef SOCKADDR_IN     sockaddr_in_t;
typedef SOCKADDR        sockaddr_t;
typedef IN_ADDR         _in_addr_t;
typedef SSIZE_T         ssize_t;
typedef struct addrinfo addrinfo_t;

#else

#error "Network is not supported for this plateform"

#endif

#define INET6_ADDRSTRLEN_INDIE 46

#endif // !GENNETWORK_HPP_
