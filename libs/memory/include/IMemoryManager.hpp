#ifndef IMEMORY_MANAGER_HPP_
#define IMEMORY_MANAGER_HPP_

#include <cstddef>

// Disable clang warning for weak vtables
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

namespace memory
{
  class IMemoryManager
  {
  public:
    virtual ~IMemoryManager()
    {
    }
    virtual void *allocate(std::size_t) = 0;
    virtual void  free(void *) = 0;
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !IMEMORY_MANAGER_HPP_
