#ifndef MT_QUEUE_HPP_
#define MT_QUEUE_HPP_

#include <mutex>
#include <queue>
#include "Semaphore.hpp"

namespace multithread
{
  template <typename T>
  class Queue
  {
  public:
    Queue() : m_mut(), m_sem(0), m_queue()
    {
    }

    ~Queue()
    {
    }

    T &front()
    {
      std::unique_lock<std::mutex> lock(m_mut);
      return (m_queue.front());
    }

    T &back()
    {
      std::unique_lock<std::mutex> lock(m_mut);
      return (m_queue.bakc());
    }

    bool empty()
    {
      std::unique_lock<std::mutex> lock(m_mut);
      return (m_queue.empty());
    }

    std::size_t size()
    {
      std::unique_lock<std::mutex> lock(m_mut);
      return (m_queue.size());
    }

    void push(T const &value)
    {
      m_mut.lock();
      m_queue.push(value);
      m_mut.unlock();
      m_sem.post();
    }

    void push(T &&value)
    {
      m_mut.lock();
      m_queue.push(std::move(value));
      m_mut.unlock();
      m_sem.post();
    }

    void pop()
    {
      m_sem.wait();
      std::unique_lock<std::mutex> lock(m_mut);
      m_queue.pop();
    }

  private:
    std::mutex    m_mut;
    Semaphore     m_sem;
    std::queue<T> m_queue;
  };
}

#endif // !MT_QUEUE_HPP_
