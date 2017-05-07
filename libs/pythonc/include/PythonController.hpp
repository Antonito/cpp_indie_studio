//
// Created by brout_m on 07/05/17.
//

#ifndef PYTHONCONTROLLER_HPP
#define PYTHONCONTROLLER_HPP

#include <pybind11.h>

namespace pythonc
{
  class PythonController
  {
  public:
    PythonController();
    ~PythonController();

  private:


    // Deleted methods
    PythonController(PythonController const&) = delete;
    PythonController &operator=(PythonController const&) = delete;
  };
}

#endif // PYTHONCONTROLLER_HPP
