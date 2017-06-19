#ifndef BARRIER_HPP_
#define BARRIER_HPP_

#include <cstdint>
#include <mutex>
#include <condition_variable>

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

namespace multithread
{
  class Barrier
  {
  public:
    explicit Barrier(std::uint32_t const nb);
    ~Barrier();
    Barrier(Barrier const &) = delete;
    Barrier &operator=(Barrier const &) = delete;

    void wait();

  private:
    std::mutex              m_mut;
    std::condition_variable m_cond;
    std::uint32_t const     m_condInit;
    std::uint32_t           m_count;
    std::uint32_t           m_curCount;
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !BARRIER_HPP_
