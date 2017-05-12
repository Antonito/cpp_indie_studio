#ifndef SEMAPHORE_HPP_
#define SEMAPHORE_HPP_

#include <mutex>
#include <condition_variable>

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

namespace multithread
{
  class Semaphore
  {
  public:
    explicit Semaphore(std::int32_t const val);
    ~Semaphore();

    bool wait();
    bool post();
    bool trywait();

    std::int32_t getValue() const;

  private:
    std::int32_t                             m_count;
    std::unique_ptr<std::mutex>              m_mut;
    std::unique_ptr<std::condition_variable> m_cond;
  };
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !SEMAPHORE_HPP_
