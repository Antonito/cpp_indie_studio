#ifndef LOGSINK_HPP_
#define LOGSINK_HPP_

#include <string>
#include <iostream>
#include <functional>
#include "LogMessage.hpp"

namespace nope
{
  namespace log
  {
    enum class LogLevel : std::size_t;

    class LogSink
    {
    public:
      LogSink(LogSink const &) = default;
      LogSink(LogSink &&) = default;
      ~LogSink() = default;

      LogSink &operator=(LogSink const &) = default;
      LogSink &operator=(LogSink &&) = default;
      void operator()(LogMessage const &msg, LogLevel) const;

      static LogSink makeOstream(std::ostream &os);
      static LogSink makeFile(std::string const &filename);

    private:
      explicit LogSink(
          std::function<void(LogMessage const &, LogLevel)> const &func);

      std::function<void(LogMessage const &, LogLevel)> m_func;
    };
  }
}

#endif // !LOGSINK_HPP_
