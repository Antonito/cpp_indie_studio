#include "multithread_stdafx.hpp"

namespace multithread
{
  Barrier::Barrier(std::uint32_t const nb)
      : m_mut(), m_cond(), m_condInit(nb), m_count(0), m_curCount(nb)
  {
  }

  Barrier::~Barrier()
  {
  }

  void wait()
  {
    std::unique_lock<std::mutex> lock(m_mut);
    unsigned int                 gen = m_count;

    if (--m_curCount == 0)
      {
	m_count++;
	m_curCount = m_count_reset_value;
	m_cond.notify_all();
	return;
      }
    while (gen == m_count)
      m_cond.wait(lock);
  }
}