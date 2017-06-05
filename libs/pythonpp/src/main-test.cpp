#include <iostream>
#include <string>
#include "PythonModule.hpp"

int main()
{
  int ret;
  std::string cc("coucou");
  std::string out;
  pythonpp::PythonModule pm("add");

  pm.feedFunctions({"addition", "modify", "readString"});
  if (pm.exec<int, int, int>(0, ret, 1, 2))
    std::cout << ret << std::endl;

  if (pm.exec<int, int>(1, ret, 1))
    std::cout << ret << std::endl;

  if (pm.exec<std::string, std::string&>(2, out, cc))
    std::cout << ret << std::endl;

  std::cout << "coucou out = " << out << std::endl;
  return (0);
}
