#include "memory_stdafx.hpp"
#include <cstdint>
#include "MemoryManager.hpp"

namespace memory
{
  MemoryManager::MemoryManager(std::size_t blockSize, std::size_t poolSize)
      : m_blockSize(blockSize), m_poolSize(poolSize), m_head(nullptr)
  {
    expandPoolSize();
  }

  MemoryManager::~MemoryManager()
  {
    MemoryBlock *next = m_head;

    while (next)
      {
	m_head = m_head->next;
	delete[] next;
	next = m_head;
      }
  }

  void *MemoryManager::allocate(std::size_t)
  {
    if (m_head == nullptr)
      {
	expandPoolSize();
      }

    MemoryBlock *head = m_head;
    m_head = m_head->next;
    return (head);
  }

  void MemoryManager::free(void *data)
  {
    MemoryBlock *head = static_cast<MemoryBlock *>(data);
    head->next = m_head;
    m_head = head;
  }

  void MemoryManager::expandPoolSize()
  {
    MemoryBlock *head =
        reinterpret_cast<MemoryBlock *>(new std::uint8_t[m_blockSize]);
    m_head = head;

    for (std::size_t i = 0; i < m_poolSize; ++i)
      {
	head->next =
	    reinterpret_cast<MemoryBlock *>(new std::uint8_t[m_blockSize]);
	head = head->next;
      }
    m_head->next = nullptr;
  }

  // Thread-safe version
  MemoryManagerThreadSafe::MemoryManagerThreadSafe(std::size_t blockSize,
                                                   std::size_t poolSize)
      : MemoryManager(blockSize, poolSize), m_mut()
  {
  }

  MemoryManagerThreadSafe::~MemoryManagerThreadSafe()
  {
  }

  void *MemoryManagerThreadSafe::allocate(std::size_t size)
  {
    std::lock_guard<std::mutex> lock(m_mut);
    return (MemoryManager::allocate(size));
  }

  void MemoryManagerThreadSafe::free(void *data)
  {
    std::lock_guard<std::mutex> lock(m_mut);
    MemoryManager::free(data);
  }
}
