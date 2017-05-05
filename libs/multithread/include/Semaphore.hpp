#ifndef SEMAPHORE_HPP_
#define SEMAPHORE_HPP_

#include <mutex>
#include <condition_variable>

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

#endif // !SEMAPHORE_HPP_