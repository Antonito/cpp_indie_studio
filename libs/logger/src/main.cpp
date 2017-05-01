#define NOPE_NO_LOG
#include "logger_stdafx.hpp"

int main()
{
  nope::log::Logger::start();
  nope::log::Logger::logLevel = nope::log::LogLevel::TRACE;
  int n = 42;
  nope::log::Log(Warning) << "oui" << n;
  return (0);
}
