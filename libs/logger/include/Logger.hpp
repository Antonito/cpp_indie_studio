#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <chrono>
#include <string>
#include <ostream>
#include <vector>
#if defined(NOPE_LOG_MULTITHREAD)
#include <mutex>
#endif
#include "LogSink.hpp"
#include "LogMessage.hpp"

namespace nope::log
{
  enum class LogLevel : int
  {
    TRACE,
    DBG,
    INFO,
    WARNING,
    ERROR
  };

  class Logger
  {
  public:
    Logger(LogLevel level = LogLevel::INFO);
    ~Logger() = default;

    void addSink(LogSink const &s);

#ifdef DEBUG
    inline LogMessage operator()(std::string &&file, size_t line);
#endif

    template <typename T>
    inline LogMessage operator<<(T const &e)
    {
      LogMessage msg(this);

      msg << e;
      return msg;
    }

    void flush(LogMessage const &) const;

    static void start();

    static LogLevel logLevel;
    static const std::chrono::time_point<std::chrono::high_resolution_clock,
                                         std::chrono::milliseconds>
        startTime;

  private:
    std::vector<LogSink> m_sinks;
    LogLevel             m_level;
#if defined(NOPE_LOG_MULTITHREAD)
    std::mutex m_mutex;
#endif
  };

  std::ostream &operator<<(std::ostream &os, LogLevel level);

  class EmptyLogger
  {
  public:
    EmptyLogger(LogLevel){};
    ~EmptyLogger() = default;

    inline void addSink(LogSink const &){};

#ifdef DEBUG
    inline EmptyLogger &operator()(std::string &&, size_t)
    {
      return *this;
    };
#endif

    template <typename T>
    inline EmptyLogger &operator<<(T const &)
    {
      return *this;
    }
  };

#if defined(NOPE_NO_LOG)
  extern EmptyLogger Trace;
  extern EmptyLogger Debug;
  extern EmptyLogger Info;
  extern EmptyLogger Warning;
  extern EmptyLogger Error;
#else
  extern Logger Trace;
#ifdef DEBUG
  extern Logger Debug;
#else
  extern EmptyLogger Debug;
#endif
  extern Logger Info;
  extern Logger Warning;
  extern Logger Error;
#endif
}

#ifdef DEBUG
#define Log(logger) logger(__FILE__, __LINE__)
#else
#define Log(logger) logger
#endif

#endif // !LOGGER_HPP_
