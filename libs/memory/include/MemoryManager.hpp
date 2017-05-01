#ifndef MEMORY_MANAGER_HPP_
#define MEMORY_MANAGER_HPP_

#include <mutex>
#include "IMemoryManager.hpp"

class MemoryManager : public IMemoryManager
{
public:
  explicit MemoryManager(std::size_t blockSize, std::size_t poolSize);
  MemoryManager &operator=(MemoryManager const &) = delete;
  MemoryManager(MemoryManager const &) = delete;
  virtual ~MemoryManager();
  virtual void *allocate(std::size_t);
  virtual void  free(void *data);

private:
  struct MemoryBlock
  {
    MemoryBlock *next;
  };

  void expandPoolSize();

  std::size_t  m_blockSize;
  std::size_t  m_poolSize;
  MemoryBlock *m_head;
};

class MemoryManagerThreadSafe : public MemoryManager
{
  explicit MemoryManagerThreadSafe(std::size_t blockSize,
                                   std::size_t poolSize);
  MemoryManagerThreadSafe &operator=(MemoryManagerThreadSafe const &) = delete;
  MemoryManagerThreadSafe(MemoryManagerThreadSafe const &) = delete;
  virtual ~MemoryManagerThreadSafe();
  virtual void *allocate(std::size_t);
  virtual void  free(void *data);

private:
  std::mutex m_mut;
};

#endif // !MEMORY_MANAGER_HPP_
