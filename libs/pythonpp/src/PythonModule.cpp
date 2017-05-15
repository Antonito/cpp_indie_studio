//
// Created by brout_m on 03/05/17.
//

#include <cstdlib>
#include <climits>
#include <PyFunctionInitializationError.hpp>
#include "PythonModule.hpp"
#include "PyInitializationError.hpp"
#include "PyFunctionInitializationError.hpp"
#include "Logger.hpp"

pythonpp::PythonModule::~PythonModule()
{
  Py_DECREF(m_module);
}

pythonpp::PythonModule::PythonModule(std::string const &moduleName)
    : m_module(nullptr), m_functions()
{
  char buff[PATH_MAX];
  char *fullpath = realpath("./", buff);
  PyObject *name;

  (void)moduleName;
  Py_SetProgramName(const_cast<char *>(moduleName.c_str()));
  if (fullpath != NULL)
    std::cout << fullpath << std::endl;
  PySys_SetPath(fullpath);
  Py_Initialize();
  if (!Py_IsInitialized())
    throw(pythonpp::PyInitializationError(
        "Error while Initializating module " + moduleName));

  name = PyString_FromString(moduleName.c_str());
  if (!name)
    throw(pythonpp::PyInitializationError("Module '" + moduleName +
                                          "' doesn't exist."));
  Py_DecRef(name);

  m_module = PyImport_Import(name);
  if (!m_module)
    throw(pythonpp::PyInitializationError("Failed to load '" + moduleName +
                                          "'"));
}

PyObject *pythonpp::PythonModule::ptr()
{
  return m_module;
}

void pythonpp::PythonModule::feedFunctions(
    std::vector<std::string> const &functionNames)
{
  std::vector<std::string> stolenNames = std::move(functionNames);

  for (std::string const &name : stolenNames)
    {
      try
      {
        m_functions.push_back(std::make_unique<PythonFunction>(m_module, name));
      }
      catch (pythonpp::PyFunctionInitializationError &err)
      {
        Log(nope::log::Warning) << err.what() << std::endl;
      }
    }
}

pythonpp::PythonFunction::~PythonFunction()
{
  Py_XDECREF(m_function);
}

pythonpp::PythonFunction::PythonFunction(
    PyObject *module, std::string const &functionName)
    : m_function(nullptr), m_name(functionName)
{
  m_function = PyObject_GetAttrString(module, functionName.c_str());
  if (!m_function)
    throw(pythonpp::PyFunctionInitializationError("Function '" + functionName +
                                                  "' doesn't exist"));
  if (!PyCallable_Check(m_function))
    throw(pythonpp::PyFunctionInitializationError("Object '" + functionName +
                                                  "' is not callable"));
}
