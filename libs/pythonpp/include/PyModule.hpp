//
// Created by brout_m on 03/05/17.
//

#ifndef CPP_INDIE_STUDIO_PYMODULE_HPP
#define CPP_INDIE_STUDIO_PYMODULE_HPP

#include <python2.7/Python.h>
#include <string>

namespace pythonpp
{
  class PyModule
  {
  public:
      PyModule(const std::string &moduleName);
      ~PyModule();

  private:
      PyObject *m_name;
      PyObject *m_module;
      PyObject *m_dict;

  };
}
#endif // CPP_INDIE_STUDIO_PYMODULE_HPP
