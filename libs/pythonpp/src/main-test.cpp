#include <iostream>
#include "PythonModule.hpp"

int main()
{
  int ret;
  std::string cc("coucou");
  std::string out;
  pythonpp::PythonModule pm("add");

  nope::log::Logger::start("python.log");
  nope::log::Logger::logLevel = nope::log::LogLevel::LOG_DEBUG;
  pm.feedFunctions({"addition", "modify", "readString", "readStringReturn0"});
  if (pm.exec<int, int, int>(0, ret, 1, 2))
    std::cout << ret << std::endl;

  if (pm.exec<int, int>(1, ret, 1))
    std::cout << ret << std::endl;

  if (pm.exec<std::string, std::string&>(2, out, cc))
    std::cout << ret << std::endl;

  if (pm.exec<int, std::string&>(3, ret, cc))
    std::cout << ret << std::endl;

  try {
    std::cout << "coucou out = " << out << std::endl;
  } catch (std::exception &err) {
    std::cout << err.what() << std::endl;
  }
  return (0);
}
