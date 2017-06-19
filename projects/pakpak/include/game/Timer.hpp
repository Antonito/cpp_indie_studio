//
// Created by brout_m on 20/04/17.
//

#ifndef CPP_PLAZZA_TIMER_HPP
#define CPP_PLAZZA_TIMER_HPP

#include <chrono>

namespace timer
{
    class Timer
    {
    public:
        Timer(int p_duree);
        bool reached() const;
        void reset();
        void start();

    private:
        bool m_started;
        std::chrono::milliseconds m_duree;
        std::chrono::system_clock::time_point m_starting_point;
    };
}

#endif //CPP_PLAZZA_TIMER_HPP
