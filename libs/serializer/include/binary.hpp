#ifndef BINARY_HPP_
#define BINARY_HPP_

#include <string>
#include <vector>
#include <cstdint>
#include <array>
#include "has_metadata.hpp"
#include "apply.hpp"
#include "byte_order.hpp"

//
// Serialize into binary
//

namespace nope
{
  namespace serialization
  {
    using buf_t = std::vector<std::uint8_t>;

    namespace detail
    {
      // Serialize object into binary (need metadata)
      template <typename T,
                bool Enable = std::is_fundamental<
                    typename std::remove_reference<T>::type>::value>
      struct to_binary_impl
      {
	// Function itself
	static void to_binary(buf_t &v, T const &t)
	{
	  nope::log::Log(Debug)
	      << "Serialize a " << typeid(T).name() << " (object)";
	  // Check if the type has metadata
	  static_assert(has_metadata<T>::result, "The type has no metadata");

	  // Loop on each metadata member
	  apply(t.m_metadata, [&v](auto e) {
	    // Serialize it's member
	    detail::to_binary_impl<typename std::remove_reference<decltype(
	        e.second)>::type>::to_binary(v, e.second);
	  });
	}
      };

      // Serialize fundamental type into binary (integer, floating point)
      template <typename T>
      struct to_binary_impl<T, true>
      {
	// Function itself
	static void to_binary(buf_t &v, T i)
	{
	  // Get the value to send in big endian
	  auto toSend = host_to_net<T>(i);

	  using toSend_t = decltype(toSend);

	  nope::log::Log(Debug)
	      << "Serialize a " << typeid(T).name() << " (fundamental) ("
	      << sizeof(toSend_t) << ')';
	  // Buffer
	  std::array<std::uint8_t, sizeof(toSend_t)> buf;

	  // Copy the value into the buffer
	  std::memcpy(buf.data(), &toSend, sizeof(toSend_t));
	  // Insert it
	  v.insert(v.end(), buf.begin(), buf.end());
	}
      };

      // Serialize string into binary
      template <>
      struct to_binary_impl<std::string, false>
      {
	// Function itself
	static void to_binary(buf_t &v, std::string const &s)
	{
	  nope::log::Log(Debug)
	      << "Serialize a " << typeid(std::string).name() << " (string)";
	  // Get the string size and convert to big endian
	  std::size_t toSend = host_to_net(s.size());
	  // Buffer
	  std::array<std::uint8_t, sizeof(std::size_t)> buf;

	  // Copy the number into the buffer
	  std::memcpy(buf.data(), &toSend, sizeof(std::size_t));
	  // Insert the size buffer
	  v.insert(v.end(), buf.begin(), buf.end());
	  // Insert the string
	  v.insert(v.end(), s.begin(), s.end());
	}
      };

      // Serialize vector into binary
      template <typename T>
      struct to_binary_impl<std::vector<T>, false>
      {
	// Function itself
	static void to_binary(buf_t &v, std::vector<T> const &s)
	{
	  nope::log::Log(Debug)
	      << "Serialize a " << typeid(std::vector<T>).name()
	      << " (vector)";
	  // Get the string size and convert to big endian
	  detail::to_binary_impl<std::uint32_t>::to_binary(v, s.size());

	  for (T const &e : s)
	    {
	      nope::log::Log(Debug)
	          << "Serialize a " << typeid(T).name() << " (vector elem)";
	      detail::to_binary_impl<T>::to_binary(v, e);
	    }
	}
      };
    }

    // Serialize an object into binary
    template <typename T>
    buf_t to_binary(T const &t)
    {
      nope::log::Log(Debug)
          << "Serialize a " << typeid(T).name() << " (to_bin)";
      // Check if the type has metadata
      static_assert(has_metadata<T>::result, "The type doesn't have metadata");
      // Vector to store the result
      buf_t v;

      // Serialize into binary
      detail::to_binary_impl<T>::to_binary(v, t);
      return (v);
    }

    //
    // Deserialize from binary
    //

    namespace detail
    {
      // Read fundamental type from binary
      template <typename T,
                bool Enable = std::is_fundamental<
                    typename std::remove_reference<T>::type>::value>
      struct read_bytes_impl
      {
	// Function itself
	static void read_bytes(std::uint8_t const *buf, T &e,
	                       std::size_t &cursor)
	{
	  // Type to read
	  using toRead_t = decltype(host_to_net<T>(e));
	  toRead_t t;

	  nope::log::Log(Debug)
	      << "Reading fundamental (" << sizeof(toRead_t) << ')';

	  // Get it from the buffer
	  std::memcpy(&t, &buf[cursor], sizeof(toRead_t));
	  // Convert it from big endian
	  e = net_to_host<T>(t);
	  // Increment cursor position
	  cursor += sizeof(toRead_t);
	}
      };

      // Read a string from binary
      template <>
      struct read_bytes_impl<std::string, false>
      {
	// Function itself
	static void read_bytes(std::uint8_t const *buf, std::string &s,
	                       std::size_t &cursor)
	{
	  // Temporary value
	  std::uint32_t _l;
	  // String length
	  std::uint32_t len;

	  // Copy length from buffer
	  std::memcpy(&_l, &buf[cursor], sizeof(std::uint32_t));
	  // Convert it from big endian
	  len = net_to_host<std::uint32_t>(_l);
	  // Increment cursor position
	  cursor += sizeof(std::uint32_t);

	  // Get the string from buffer
	  s = std::string(reinterpret_cast<const char *>(&buf[cursor]), len);
	  cursor += len;
	}
      };

      // Deserialize an object from binary (need metadata)
      template <typename T,
                bool Enable = std::is_fundamental<
                    typename std::remove_reference<T>::type>::value>
      struct from_binary_impl
      {
	// Function itself
	static void from_binary(T &t, buf_t const &v, std::size_t &cursor)
	{
	  // Check if the type has metadata
	  static_assert(has_metadata<T>::result,
	                "The type doesn't have metadata");

	  nope::log::Log(Debug)
	      << "Deserialize a " << typeid(T).name() << " (object)";

	  // Deserialize each member
	  apply(t.m_metadata, [&v, &cursor](auto e) {
	    detail::from_binary_impl<typename std::remove_reference<decltype(
	        e.second)>::type>::from_binary(e.second, v, cursor);
	  });
	}
      };

      // Deserialize fundamental type (integer, floating point) from binary
      template <typename T>
      struct from_binary_impl<T, true>
      {
	// Function itself
	static void from_binary(T &t, buf_t const &v, std::size_t &cursor)
	{
	  nope::log::Log(Debug)
	      << "Deserialize a " << typeid(T).name() << " (fundamental)";
	  // Read fundamental type from buffer
	  detail::read_bytes_impl<T>::read_bytes(v.data(), t, cursor);
	}
      };

      // Deserialize string from binary
      template <>
      struct from_binary_impl<std::string, false>
      {
	// Function itself
	static void from_binary(std::string &s, buf_t const &v,
	                        std::size_t &cursor)
	{
	  nope::log::Log(Debug)
	      << "Deserialize a " << typeid(std::string).name() << " (string)";
	  // Read a string from buffer
	  detail::read_bytes_impl<std::string>::read_bytes(v.data(), s,
	                                                   cursor);
	}
      };

      // Deserialize vector from binary
      template <typename T>
      struct from_binary_impl<std::vector<T>, false>
      {
	// Function itself
	static void from_binary(std::vector<T> &s, buf_t const &v,
	                        std::size_t &cursor)
	{
	  nope::log::Log(Debug)
	      << "Deserialize a " << typeid(std::vector<T>).name()
	      << " (vector)";

	  uint32_t tmp;
	  uint32_t len;

	  detail::from_binary_impl<std::uint32_t>::from_binary(len, v, cursor);

	  s.resize(len);
	  for (T &t : s)
	    {
	      nope::log::Log(Debug) << "Deserialize a " << typeid(T).name()
	                            << " (vector element)";
	      detail::from_binary_impl<T>::from_binary(t, v, cursor);
	    }
	}
      };
    }

    // Deserialize object from binary
    template <typename T>
    T from_binary(buf_t const &v)
    {
      nope::log::Log(Debug)
          << "Deserialize a " << typeid(T).name() << " (from_bin)";

      // Check if the type has metadata
      static_assert(has_metadata<T>::result, "The type doesn't have metadata");
      // Cursor into the binary buffer
      std::size_t cursor = 0;
      // Resulting object
      T t;

      // Deserialize from binary
      detail::from_binary_impl<T>::from_binary(t, v, cursor);

      return (t);
    }
  }
}

#endif // !BINARY_HPP_
