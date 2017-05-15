#include <iostream>
#include "PythonModule.hpp"

int main()
{
  int ret;
  pythonpp::PythonModule pm("./add.py");

  /*  pm.feedFunctions({"addition", "modify"});
  if (pm.exec(0, ret, 1, 2))
    std::cout << ret << std::endl;

  if (pm.exec(1, ret, 1))
    std::cout << ret << std::endl;
  */
  return (0);
}
