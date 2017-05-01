#ifndef IMEMORY_MANAGER_HPP_
#define IMEMORY_MANAGER_HPP_

#include <cstddef>

namespace memory
{
  class IMemoryManager
  {
  public:
    virtual ~IMemoryManager(){};
    virtual void *allocate(std::size_t) = 0;
    virtual void  free(void *) = 0;
  };
}

#endif // !IMEMORY_MANAGER_HPP_
