#include "multithread_stdafx.hpp"

namespace multithread
{
  Semaphore::Semaphore(std::int32_t const val)
      : m_count(val), m_mut(std::make_unique<std::mutex>()),
        m_cond(std::make_unique<std::condition_variable>())
  {
  }

  Semaphore::~Semaphore()
  {
  }

  bool Semaphore::wait()
  {
    std::unique_lock<std::mutex> lock(*m_mut);
    while (m_count == 0)
      {
	m_cond->wait(lock);
      }
    --m_count;
    return (true);
  }

  bool Semaphore::post()
  {
    std::unique_lock<std::mutex> lock(*m_mut);
    m_cond->notify_one();
    ++m_count;
    return (true);
  }

  bool Semaphore::trywait()
  {
    std::unique_lock<std::mutex> lock(*m_mut);
    if (m_count == 0)
      {
	return (false);
      }
    --m_count;
    return (true);
  }

  std::int32_t Semaphore::getValue() const
  {
    return (m_count);
  }
}
