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
    enum class LogLevel : int;

    class LogSink
    {
    public:
      ~LogSink() = default;
      void operator()(LogMessage const &msg, LogLevel) const;

      static LogSink makeOstream(std::ostream &os);
      static LogSink makeFile(std::string const &filename);

    private:
      LogSink(std::function<void(LogMessage const &, LogLevel)> func);
      // operator LogSink(std::function<void(LogMessage const &)>);

      std::function<void(LogMessage const &, LogLevel)> m_func;
    };
  }
}

#endif // !LOGSINK_HPP_