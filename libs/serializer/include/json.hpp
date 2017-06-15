#pragma once

#include <iostream>
#include <sstream>
#include <tuple>
#include <memory>
#include <cmath>
#include <cstring>
#include <cctype>
#include "apply.hpp"
#include "has_metadata.hpp"

//
// Serialize into JSON
//

namespace nope
{
  namespace serialization
  {
    namespace detail
    {
      // Serialize an object (need metadata)
      template <typename T,
                bool Enable = std::is_fundamental<
                    typename std::remove_reference<T>::type>::value>
      struct to_json_impl
      {
	// Function itself
	static void to_json_(std::stringstream &json, T const &t)
	{
	  // Check if there is metadata
	  static_assert(has_metadata<T>::result, "The type has no metadata");
	  // Get the number of members
	  std::size_t n = std::tuple_size<decltype(t.m_metadata)>::value - 1;

	  json << '{';
	  // Loop on each member (e is a std::pair<const char *member_name, T
	  // &member>)
	  apply(t.m_metadata, [&json, &n](auto &e) {
	    // Insert the name
	    json << '"' << e.first << "\":";
	    // Convert the value to JSON
	    to_json_impl<decltype(e.second)>::to_json_(json, e.second);
	    // If the element is not the last, insert a comma
	    if (n > 0)
	      {
		json << ',';
	      }
	    n--;
	  });
	  json << '}';
	}
      };

      // Serialize a string
      template <>
      struct to_json_impl<std::string &, false>
      {
	// Function itself
	static void to_json_(std::stringstream &json, std::string const &s)
	{
	  json << '"' << s << '"';
	}
      };

      // Serialize a fundamental type (integer and floating points)
      template <typename T>
      struct to_json_impl<T, true>
      {
	// Function itself
	static void to_json_(std::stringstream &json, T const &i)
	{
	  json << i;
	}
      };
    }

    // Convert a type to json
    template <typename T>
    std::string to_json(T const &t)
    {
      // Check if the type has metadata
      static_assert(has_metadata<T>::result, "The type doesn't have metadata");
      // Store the resulting JSON
      std::stringstream json;

      // Convert T to JSON
      detail::to_json_impl<T>::to_json_(json, t);
      return (json.str());
    }

    //
    // Deserialize from JSON
    //

    namespace detail
    {
      // Forward declaration
      template <typename T>
      bool fetch_member_json(T &t, std::stringstream &ss);

      // Deserialize any object (need metadata)
      template <typename T, bool Enable = std::is_fundamental<T>::value>
      struct from_json_impl
      {
	// Function itself
	static void from_json(T &t, std::stringstream &ss)
	{
	  // Store the current char
	  char c;

	  // Go to the next char which is not a space
	  while (ss.get(c) && std::isspace(c))
	    ;

	  // Check if it's an json object
	  if (c != '{')
	    {
	      throw std::invalid_argument("Ill-formed JSON");
	    }

	  // Deserialize each member
	  while (fetch_member_json(t, ss))
	    ;

	  // Check if we leave an object
	  if (!ss.get(c) || c != '}')
	    {
	      throw std::invalid_argument("Ill-formed JSON");
	    }
	}
      };

      // Deserialize a string
      template <>
      struct from_json_impl<std::string, false>
      {
	static void from_json(std::string &s, std::stringstream &ss)
	{
	  // Is the character escaped
	  bool escaped = false;
	  // Current char
	  char c;

	  // Go to the next char which is not a space
	  while (ss.get(c) && std::isspace(c))
	    ;

	  // Check if this is a double quote
	  if (c != '"')
	    {
	      throw std::invalid_argument("Ill-formed JSON");
	    }

	  // Get each char
	  while (ss.get(c))
	    {
	      // If the character is escaped, add it anyway
	      if (escaped)
		{
		  s += c;
		  escaped = false;
		}
	      // Else if it's an escaping char, escape
	      else if (c == '\\')
		{
		  escaped = true;
		}
	      // Else if it's not escaped and double quote, end of string
	      else if (c == '"')
		{
		  break;
		}
	      // Else it's a normal char, add it
	      else
		{
		  s += c;
		}
	    }
	  // Check if it was a string ending and not end of stream
	  if (c != '"')
	    {
	      throw std::invalid_argument("Ill-formed JSON");
	    }
	}
      };

      // Deserialize a fundamental type (integer, floating point)
      template <typename T>
      struct from_json_impl<T, true>
      {
	// Function itself
	static void from_json(T &res, std::stringstream &ss)
	{
	  // Is it a floating point?
	  bool fp = false;
	  // Decimal power
	  int p = 0;
	  // Sign
	  int sign = 1;
	  // Current char
	  char c;

	  // Set the result to 0
	  res = static_cast<T>(0.0);

	  // Go to the next char which is not a space
	  while (ss.get(c) && std::isspace(c))
	    ;

	  // If it's a minus sign, change sign
	  if (c == '-')
	    {
	      sign = -1;
	    }
	  else
	    {
	      ss.unget();
	    }

	  // Loop on each ciffer
	  while (ss.get(c))
	    {
	      // If c is a digit, add it
	      if (std::isdigit(c))
		{
		  // If it's a floating point value, add it as decimal
		  if (fp)
		    {
		      res += static_cast<T>((c - '0') / std::pow(10, p));
		      ++p;
		    }
		  // Else add it as a unit
		  else
		    {
		      res = 10 * res + c - '0';
		    }
		}
	      // Else if it's a floating point
	      else if (c == '.')
		{
		  // Check if it's not already a floating point
		  if (fp)
		    {
		      throw std::invalid_argument("Ill-formed JSON number");
		    }
		  fp = true;
		  p = 1;
		}
	      // Else it's an invalid character
	      else
		{
		  ss.unget();
		  break;
		}
	    }
	  // Apply the sign
	  res *= static_cast<T>(sign);
	}
      };

      // Deserialize a member based on the name
      template <typename T>
      bool fetch_member_json(T &t, std::stringstream &ss)
      {
	// Check if the type has metadata
	static_assert(has_metadata<T>::result, "Type doesn't have metadata");
	// Current char
	char c;
	// Member name
	std::string name;

	// Go to the next valid char
	while (ss.get(c) && std::isspace(c))
	  ;

	ss.unget();
	// If it's a closing object, don't fetch member
	if (c == '}')
	  {
	    return (false);
	  }

	// Get the member name
	from_json_impl<std::string>::from_json(name, ss);

	// Go to the next valid char
	while (ss.get(c) && std::isspace(c))
	  ;

	if (c != ':')
	  {
	    throw std::invalid_argument("Ill-formed JSON");
	  }

	// Used to check if the member was found
	bool done = false;

	// Search in every metadata member
	apply(t.m_metadata, [&name, &ss, &done](auto &e) {
	  // If the name match this member's name
	  if (name == e.first)
	    {
	      // Deserialize and fill the member
	      from_json_impl<typename std::remove_reference<decltype(
	          e.second)>::type>::from_json(e.second, ss);
	      done = true;
	    }
	});

	// If done is false, the member was not found in metadata
	if (!done)
	  {
	    throw std::invalid_argument("Member '" + name + "' is unknown");
	  }

	// Go to the next char which is not a space
	while (ss.get(c) && std::isspace(c))
	  ;

	if (c != ',')
	  {
	    ss.unget();
	  }
	return (true);
      }
    }

    // Deserialize a type from json
    template <typename T>
    T from_json(std::string const &s)
    {
      // Check if the type has metadata
      static_assert(has_metadata<T>::result, "The type doesn't have metadata");
      // Store the input json
      std::stringstream ss;
      // Resulting object
      T t;

      // Put the input into the stream
      ss << s;
      // Deserialize
      detail::from_json_impl<T>::from_json(t, ss);
      return (t);
    }
  }
}

