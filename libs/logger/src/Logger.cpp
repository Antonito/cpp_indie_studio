#include "logger_stdafx.hpp"

namespace nope
{
  namespace log
  {
    // Do not touch
    LogLevel Logger::logLevel = LogLevel::LOG_INFO;

    std::chrono::time_point<std::chrono::high_resolution_clock,
                            std::chrono::milliseconds> const
        Logger::startTime =
            std::chrono::time_point_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now());
// Creation

#if defined(NOPE_NO_LOG)
    EmptyLogger Trace(LogLevel::LOG_TRACE);
    EmptyLogger Debug(LogLevel::LOG_DEBUG);
    EmptyLogger Info(LogLevel::LOG_INFO);
    EmptyLogger Warning(LogLevel::LOG_WARNING);
    EmptyLogger Error(LogLevel::LOG_ERROR);
#else
    Logger Trace(LogLevel::LOG_TRACE);
#ifdef DEBUG
    Logger Debug(LogLevel::LOG_DEBUG);
#else
    EmptyLogger Debug(LogLevel::LOG_DEBUG);
#endif
    Logger Info(LogLevel::LOG_INFO);
    Logger Warning(LogLevel::LOG_WARNING);
    Logger Error(LogLevel::LOG_ERROR);
#endif

    Logger::Logger(LogLevel level)
        : m_sinks(), m_level(level)
#if defined(NOPE_LOG_MULTITHREAD)
          ,
          m_mutex()
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
    LogMessage Logger::operator()(std::string &&file, std::size_t line)
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

    void Logger::start(std::string const &filename)
    {
      LogSink console = LogSink::makeOstream(std::cout);
      LogSink file = LogSink::makeFile(filename);

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
	case LogLevel::LOG_TRACE:
	  os << "{{TRACE}}";
	  break;
	case LogLevel::LOG_DEBUG:
	  os << "[DEBUG]\t";
	  break;
	case LogLevel::LOG_INFO:
	  os << "[INFO]\t";
	  break;
	case LogLevel::LOG_WARNING:
	  os << "**WARNING**";
	  break;
	case LogLevel::LOG_ERROR:
	  os << "!!ERROR!!";
	  break;
	}
      os << "\t";
      return os;
    }
  }
}
