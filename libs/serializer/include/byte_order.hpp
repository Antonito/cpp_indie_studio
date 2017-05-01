#pragma once

// Convert short (16 bits) to big endian
#ifndef htons
#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#define htons(X) (((X & 0xFF00) >> 8) | ((X & 0x00FF) << 8))
#elif (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define htons(X) (X)
#else
#error "Unknown endianness"
#endif
#endif

// Convert long (32 bits) to big endian
#ifndef htonl
#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#define htonl(X) (((X & 0xFF000000) >> 24) | ((X & 0x00FF0000) >> 8) |  \
                  ((X & 0x0000FF00) << 8) | ((X & 0x000000FF) << 24))
#elif (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define htonl(X) (X)
#else
#error "Unknown endianness"
#endif
#endif

// Convert long long (64 bits) to big endian
#ifndef htonll
#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#define htonll(X) (((X & 0xFF00000000000000) >> 56) | \
                   ((X & 0x00FF000000000000) >> 40) | \
                   ((X & 0x0000FF0000000000) >> 24) | \
                   ((X & 0x000000FF00000000) >> 8) | \
                   ((X & 0x00000000FF000000) << 8) | \
                   ((X & 0x0000000000FF0000) << 24) | \
                   ((X & 0x000000000000FF00) << 40) | \
                   ((X & 0x00000000000000FF) << 56))
#elif (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define htonll(X) (X)
#else
#error "Unknown endianness"
#endif
#endif

// Convert short (16 bits) from big endian
#ifndef ntohs
#define ntohs(X) htons(X)
#endif

// Convert long (32 bits) from big endian
#ifndef ntohl
#define ntohl(X) htonl(X)
#endif

// Convert long long (64 bits) from big endian
#ifndef ntohll
#define ntohll(X) htonll(X)
#endif

namespace nope
{
  namespace serialization
  {
    namespace detail
    {
      template <typename T, std::size_t S = sizeof(T) * 8>
      struct net_to_host_impl
      {
        // If no specialisation found (16, 32, or 64 bits), compilation should fail
        // because there is no implementation here
      };

      // 8 bit integer
      template <typename T>
      struct net_to_host_impl<T, 8>
      {
        static T net_to_host(T t)
        {
          return (t);
        }
      };

      // 16 bit integer
      template <typename T>
      struct net_to_host_impl<T, 16>
      {
        static T net_to_host(T t)
        {
          return (ntohs(t));
        }
      };

      // 32 bit integer
      template <typename T>
      struct net_to_host_impl<T, 32>
      {
        static T net_to_host(T t)
        {
          return (ntohl(t));
        }
      };

      // 32 bit floating point (need conversion to integer)
      template <>
      struct net_to_host_impl<float, 32>
      {
        static float net_to_host(float t)
        {
          std::uint32_t u = ntohl(*reinterpret_cast<std::uint32_t*>(&t));
          return (*reinterpret_cast<float*>(&u));
        }
      };

      // 64 bit integer
      template <typename T>
      struct net_to_host_impl<T, 64>
      {
        static T net_to_host(T t)
        {
          return (ntohll(t));
        }
      };

      // 64 bit floating point (need conversion to integer)
      template <>
      struct net_to_host_impl<double, 64>
      {
        static double net_to_host(double t)
        {
          std::uint64_t u = ntohll(*reinterpret_cast<std::uint64_t*>(&t));
          return (*reinterpret_cast<double *>(&u));
        }
      };
    }

    // Call the right macro based on the type size
    template <typename T>
    T net_to_host(T val)
    {
      return (detail::net_to_host_impl<T>::net_to_host(val));
    }

    namespace detail
    {
      template <typename T, std::size_t S = sizeof(T) * 8>
      struct host_to_net_impl
      {
        // If no specialisation found (16, 32, or 64 bits), compilation should fail
        // because there is no implementation here
      };

      // 8 bit integer
      template <typename T>
      struct host_to_net_impl<T, 8>
      {
        static T host_to_net(T t)
        {
          return (t);
        }
      };

      // 16 bit integer
      template <typename T>
      struct host_to_net_impl<T, 16>
      {
        static T host_to_net(T t)
        {
          return (htons(t));
        }
      };

      // 32 bit integer
      template <typename T>
      struct host_to_net_impl<T, 32>
      {
        static T host_to_net(T t)
        {
          return (htonl(t));
        }
      };

      // 32 bit floating point (need conversion to integer)
      template <>
      struct host_to_net_impl<float, 32>
      {
        static float host_to_net(float t)
        {
          std::uint32_t u = htonl(*reinterpret_cast<std::uint32_t*>(&t));
          return (*reinterpret_cast<float *>(&u));
        }
      };

      // 64 bit integer
      template <typename T>
      struct host_to_net_impl<T, 64>
      {
        static T host_to_net(T t)
        {
          return (htonll(t));
        }
      };

      // 64 bit floating point (need conversion to integer)
      template <>
      struct host_to_net_impl<double, 64>
      {
        static double host_to_net(double t)
        {
          std::uint64_t u = htonll(*reinterpret_cast<std::uint64_t*>(&t));
          return (*reinterpret_cast<double *>(&u));
        }
      };
    }

    // Call the right macro based on the type size
    template <typename T>
    T host_to_net(T val)
    {
      return (detail::host_to_net_impl<T>::host_to_net(val));
    }
  }
}