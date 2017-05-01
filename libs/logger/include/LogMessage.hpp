#ifndef LOGMESSAGE_HPP_
#define LOGMESSAGE_HPP_

#include <chrono>
#include <string>
#include <ostream>
#include <sstream>

namespace nope
{
  namespace log
  {
    class Logger;

    struct LogMessage
    {
      LogMessage() = delete;
      LogMessage(LogMessage const &) = default;
      LogMessage(LogMessage &&) = default;
      explicit LogMessage(Logger *src);
      ~LogMessage();

#ifdef DEBUG
      LogMessage(Logger *src, std::string &&filename, std::size_t line);
#endif

      LogMessage &operator=(LogMessage const &) = default;
      LogMessage &operator=(LogMessage &&) = default;

      std::string                                    getMessage() const;
      std::chrono::duration<long, std::milli> const &getTime() const;
#ifdef DEBUG
      struct Meta
      {
	Meta();
	std::string file;
	std::size_t line;
      };
      Meta meta;
#endif

      template <typename T>
      LogMessage &operator<<(T const &e)
      {
	m_buf << e;
	return *this;
      }

      LogMessage &operator<<(std::ostream &(*fn)(std::ostream &os));

      const std::chrono::milliseconds time;

    private:
      std::stringstream m_buf;
      Logger *          m_src;
    };

#ifdef DEBUG
    std::ostream &operator<<(std::ostream &os, LogMessage::Meta const &meta);
#endif
  }
}
#endif // !LOGMESSAGE_HPP_
