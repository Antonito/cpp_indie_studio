//
// Created by brout_m on 20/04/17.
//

#include <chrono>
#include "Logger.hpp"
#include "Timer.hpp"

namespace game
{
  Timer::Timer(int p_duree)
      : m_started(false), m_duree(p_duree), m_starting_point(), m_save_point()
  {
  }

  bool Timer::reached() const
  {
    return (m_started &&
            std::chrono::system_clock::now() - m_starting_point > m_duree);
  }

  void Timer::reset()
  {
    start();
  }

  void Timer::start()
  {
    m_started = true;
    m_save_point = m_starting_point = std::chrono::system_clock::now();
  }

  void Timer::save()
  {
    m_save_point = std::chrono::system_clock::now();
  }

  std::chrono::milliseconds Timer::elapsedTime() const
  {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        m_save_point - m_starting_point);
  }

  bool Timer::isStarted() const
  {
    return m_started;
  }

  void Timer::reset(int duree)
  {
    std::chrono::milliseconds newDurre(duree);
    m_duree = std::move(newDurre);
    start();
  }
}
