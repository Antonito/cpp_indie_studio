#pragma once

#include <tuple>

//
// Apply a function on all elements of a tuple
//
// There is a non const AND a const implementation which are exactly the same
// so there will only be comments on the first implementation
//
namespace nope
{
  namespace serialization
  {
    namespace detail
    {

      // Non const version

      // N is the tuple size, I is the current element
      template <std::size_t N, std::size_t I = 0>
      struct impl
      {
        template <typename T, typename ...Args>
        static void apply(std::tuple<Args...> &t, T fn)
        {
          // Call fn with the element I
          fn(std::get<I>(t));
          // Call recursively with the next parameter
          impl<N, I + 1>::apply(t, fn);
        }
      };

      // This is the stop condition, when I == N
      template <std::size_t N>
      struct impl<N, N>
      {
        template <typename T, typename ...Args>
        static void apply(std::tuple<Args...> &, T)
        {
          // Don't do anything
        }
      };

      // Const version (exact same implementation, with const)

      template <std::size_t N, std::size_t I = 0>
      struct impl_c
      {
        template <typename T, typename ...Args>
        static void apply(std::tuple<Args...> const &t, T fn)
        {
          fn(std::get<I>(t));
          impl_c<N, I + 1>::apply(t, fn);
        }
      };

      template <std::size_t N>
      struct impl_c<N, N>
      {
        template <typename T, typename ...Args>
        static void apply(std::tuple<Args...> const &, T)
        {
        }
      };
    }

    // Non const version

    // Takes a tuple as parameter, and a functor
    template <typename T, typename ...Args>
    void apply(std::tuple<Args...> &t, T fn)
    {
      // Call implementation with N = tuple size
      detail::impl<std::tuple_size<std::tuple<Args...>>::value>::apply(t, fn);
    }

    // Const version (again, only a const added)

    template <typename T, typename ...Args>
    void apply(std::tuple<Args...> const &t, T fn)
    {
      detail::impl_c<std::tuple_size<std::tuple<Args...>>::value>::apply(t, fn);
    }
  }
}
