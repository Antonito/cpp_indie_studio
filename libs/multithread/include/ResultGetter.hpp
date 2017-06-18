#ifndef RESULT_GETTER_H_
#define RESULT_GETTER_H_

#include <mutex>
#include <condition_variable>
#include <memory>

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

namespace multithread
{
  template <typename T>
  class ResultGetter
  {
  public:
    explicit ResultGetter(T &data)
        : m_data(data), m_mut(std::make_unique<std::mutex>()),
          m_cond(std::make_unique<std::condition_variable>())
    {
    }

    ~ResultGetter()
    {
    }

    ResultGetter(ResultGetter const &other)
        : m_data(other.m_data), m_mut(other.m_mut), m_cond(other.m_cond)
    {
    }

    ResultGetter(ResultGetter &other)
        : m_data(other.m_data), m_mut(other.m_mut), m_cond(other.m_cond)
    {
    }

    ResultGetter &operator=(ResultGetter const &) = delete;

    ResultGetter(ResultGetter &&) = delete;

    T &getData()
    {
      return (m_data);
    }

    std::mutex &getMut()
    {
      return (*m_mut);
    }

    void notify()
    {
      m_cond->notify_one();
    }

    void waitForNotif()
    {
      std::unique_lock<std::mutex> lock(*m_mut);
      m_cond->wait(lock);
    }

  private:
    T &                                      m_data;
    std::shared_ptr<std::mutex>              m_mut;
    std::shared_ptr<std::condition_variable> m_cond;
  };
}

// Disable clang warning for implicit padding
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !RESULT_GETTER_H_
