#include "logger_stdafx.hpp"

namespace nope::log
{
  // Do not touch
  std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::milliseconds> const Logger::startTime =
    std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now());

  LogLevel Logger::logLevel = LogLevel::INFO;

#if defined(NOPE_NO_LOG)
  EmptyLogger Trace(LogLevel::TRACE);
  EmptyLogger Debug(LogLevel::DBG);
  EmptyLogger Info(LogLevel::INFO);
  EmptyLogger Warning(LogLevel::WARNING);
  EmptyLogger Error(LogLevel::ERROR);
#else
  Logger Trace(LogLevel::TRACE);
#ifdef DEBUG
  Logger Debug(LogLevel::DBG);
#else
  EmptyLogger Debug(LogLevel::DBG);
#endif
  Logger Info(LogLevel::INFO);
  Logger Warning(LogLevel::WARNING);
  Logger Error(LogLevel::ERROR);
#endif


  Logger::Logger(LogLevel level) : m_level(level)
#if defined(NOPE_LOG_MULTITHREAD)
    , m_mutex()
#endif
  {
  }

  void Logger::addSink(LogSink const &s)
  {
#if defined(NOPE_LOG_MULTITHREAD)
    m_mutex.lock();
#endif
    m_sinks.push_back(s);
#if defined(NOPE_LOG_MULTITHREAD)
    m_mutex.unlock();
#endif
  }

#ifdef DEBUG
  LogMessage Logger::operator()(std::string &&file, size_t line)
  {
    return LogMessage(this, std::move(file), line);
  }
#endif

  void Logger::flush(LogMessage const &msg) const
  {
#if defined(NOPE_LOG_MULTITHREAD)
    m_mutex.lock();
#endif
    if (m_level >= logLevel)
    {
      for (auto &s : m_sinks)
      {
        s(msg, m_level);
      }
    }
#if defined(NOPE_LOG_MULTITHREAD)
    m_mutex.unlock();
#endif
  }

  void Logger::start()
  {
    LogSink console = LogSink::makeOstream(std::cout);
    LogSink file = LogSink::makeFile("nope.log");

    Trace.addSink(console);
    Debug.addSink(console);
    Info.addSink(console);
    Warning.addSink(console);
    Error.addSink(console);

    Debug.addSink(file);
    Warning.addSink(file);
    Error.addSink(file);
  }

  std::ostream &operator<<(std::ostream &os, LogLevel level)
  {
    switch (level)
    {
    case LogLevel::TRACE:
      os << "{{TRACE}}";
      break;
#ifdef DEBUG
    case LogLevel::DBG:
      os << "[DEBUG]\t";
      break;
#endif
    case LogLevel::INFO:
      os << "[INFO]\t";
      break;
    case LogLevel::WARNING:
      os << "**WARNING**";
      break;
    case LogLevel::ERROR:
      os << "!!ERROR!!";
      break;
    default:
      os << "? Unknown ?";
    }
    os << "\t";
    return os;
  }
}
