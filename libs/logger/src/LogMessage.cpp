#include "logger_stdafx.hpp"

namespace nope
{
  namespace log
  {
    LogMessage::LogMessage(Logger *src)
        :
#ifdef DEBUG
          meta(),
#endif
          time(std::chrono::time_point_cast<std::chrono::milliseconds>(
                   std::chrono::high_resolution_clock::now()) -
               Logger::startTime),
          m_buf(), m_src(src)
    {
    }

    LogMessage::~LogMessage()
    {
      m_src->flush(*this);
    }

#ifdef DEBUG
    LogMessage::LogMessage(Logger *src, std::string &&filename,
                           std::size_t line)
        : LogMessage(src)
    {
      meta.file = std::move(filename);
      meta.line = line;
    }
#endif

    std::string LogMessage::getMessage() const
    {
      return m_buf.str();
    }

    LogMessage &LogMessage::operator<<(std::ostream &(*fn)(std::ostream &os))
    {
      fn(m_buf);
      return *this;
    }

#ifdef DEBUG
    LogMessage::Meta::Meta() : file(), line(0)
    {
    }

    std::ostream &operator<<(std::ostream &os, LogMessage::Meta const &meta)
    {
      os << meta.file << ":" << meta.line;
      return os;
    }
#endif
  }
}
