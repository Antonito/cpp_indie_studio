#pragma once

#include <tuple>

//
// Check if the type has metadata
//
// This uses SFINAE
// If there is no error while using decltype on the m_metadata member
// deduce will return true_type
// else if will return false_type
//
// Using this we can call deduce with U = T and store the resulting value
// stored in those types (true or false) in result
//

namespace nope
{
  namespace serialization
  {
    template <typename T>
    class has_metadata
    {
      template <typename U>
      constexpr static std::true_type deduce(decltype(U::m_metadata)*);
      template <typename>
      constexpr static std::false_type deduce(...);
    public:
      constexpr static bool result = decltype(deduce<typename std::remove_reference<T>::type>(nullptr))::value;
    };
  }
}