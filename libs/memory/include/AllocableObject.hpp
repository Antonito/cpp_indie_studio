#ifndef ALLOCABLE_OBJECT_HPP_
#define ALLOCABLE_OBJECT_HPP_

#include "MemoryManager.hpp"

extern MemoryManager gMemoryManager;

class AllocableObject
{
  // TODO: Singleton
public:
  inline void *operator new(std::size_t size)
  {
    return (gMemoryManager.allocate(size));
  }

  inline void operator delete(void *ptr)
  {
    gMemoryManager.free(ptr);
  }
};

#endif // !ALLOCABLE_OBJECT_HPP_
