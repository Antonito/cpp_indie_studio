//
// Created by brout_m on 03/05/17.
//

#ifndef CPP_INDIE_STUDIO_PYMODULE_HPP
#define CPP_INDIE_STUDIO_PYMODULE_HPP

#include <python2.7/Python.h>
#include <string>
#include <map>
#include <vector>
#include <memory>

namespace pythonpp
{
  class PyModule
  {
  public:
    PyModule(std::string const &moduleName);
    ~PyModule();
    PyObject *ptr();
    void feedFunctions(std::vector<std::string> &functionNames);

  private:
    PyObject *m_module;
    std::map<std::string, std::unique_ptr<PyFunction>> m_functions;

    class PyFunction
    {
    public:
      PyFunction(PyModule &module, std::string const &functionName);
      ~PyFunction();

    private:
      PyObject *m_function;
    };
  };
}
#endif // CPP_INDIE_STUDIO_PYMODULE_HPP
