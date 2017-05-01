#include "logger_stdafx.hpp"

namespace nope
{
  namespace log
  {
    LogSink::LogSink(
        std::function<void(LogMessage const &, LogLevel)> const &func)
        : m_func(func)
    {
    }

    void LogSink::operator()(LogMessage const &msg, LogLevel level) const
    {
      m_func(msg, level);
    }

    LogSink LogSink::makeOstream(std::ostream &os)
    {
      os << "Type\t\tTime\tMessage" << std::endl;

      return LogSink([&os](LogMessage const &msg, LogLevel level) {
	auto time = std::chrono::milliseconds(msg.time);

	os << level << (time.count() / 1000) << "." << std::setfill('0')
	   << std::setw(3) << (time.count() % 1000) << "\t" << msg.getMessage()
	   << std::endl;
      });
    }

    LogSink LogSink::makeFile(std::string const &filename)
    {
      auto file = std::make_shared<std::ofstream>(filename.c_str());

      return LogSink([file](LogMessage const &msg, LogLevel level) {
	auto time = std::chrono::milliseconds(msg.time);

	*file << level << (time.count() / 1000) << "." << std::setfill('0')
	      << std::setw(3) << (time.count() % 1000) << "\t"
#ifdef DEBUG
	      << "(" << msg.meta << ") : "
#endif
	      << msg.getMessage() << std::endl;
      });
    }
  }
}
