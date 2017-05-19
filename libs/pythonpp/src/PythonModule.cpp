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
  Py_Finalize();
}

pythonpp::PythonModule::PythonModule(std::string const &moduleName)
    : m_module(nullptr), m_functions()
{
  char buff[PATH_MAX];
  PyObject *name;

  printf("started init\n");
  Py_Initialize();
  PySys_SetPath(realpath(".", buff));
  if (!Py_IsInitialized())
    throw(pythonpp::PyInitializationError(
        "Error while Initializating module " + moduleName));
  name = PyString_FromString(moduleName.c_str());
  if (!name)
    throw(pythonpp::PyInitializationError("Module '" + moduleName +
                                          "' doesn't exist."));
  m_module = PyImport_Import(name);
  if (!m_module)
    throw(pythonpp::PyInitializationError("Failed to load '" + moduleName +
                                          "'"));
  Py_DecRef(name);
}

PyObject *pythonpp::PythonModule::ptr()
{
  return m_module;
}

void pythonpp::PythonModule::feedFunctions(
    std::vector<std::string> const &functionNames)
{
  std::vector<std::string> stolenNames = std::move(functionNames);

  printf("starting function feed\n");
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
  printf("finished function feed\n");
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
  std::cout << "function : " << functionName << " pushed" << std::endl;
}
