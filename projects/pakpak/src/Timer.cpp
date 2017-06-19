//
// Created by brout_m on 20/04/17.
//

#include <chrono>
#include "Timer.hpp"

timer::Timer::Timer(int p_duree) :
        m_started(false),
        m_duree(p_duree)
{

}

bool timer::Timer::reached() const
{
  return (m_started && std::chrono::system_clock::now() - m_starting_point > m_duree);
}

void timer::Timer::reset()
{
    start();
}

void timer::Timer::start()
{
    m_started = true;
    m_starting_point = std::chrono::system_clock::now();
}
