//
// Created by brout_m on 03/05/17.
//

#include <cstdlib>
#include <climits>
#include "PyFunctionInitializationError.hpp"
#include "PythonModule.hpp"
#include "PyInitializationError.hpp"
#include "Logger.hpp"

pythonpp::PythonModule::~PythonModule()
{
  Py_Finalize();
}

pythonpp::PythonModule::PythonModule(std::string const &moduleName)
    : m_module(nullptr), m_functions(), m_moduleName(moduleName)
{
  char      buff[PATH_MAX];
  PyObject *name;

  Log(nope::log::Debug) << "Starting python module '" << moduleName << "'";
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

  Log(nope::log::Debug) << "Starting module '" << m_moduleName
                        << "' function feed...";
  for (std::string const &name : stolenNames)
    {
      try
	{
	  m_functions.push_back(
	      std::make_unique<PythonFunction>(m_module, name));
	}
      catch (pythonpp::PyFunctionInitializationError &err)
	{
	  Log(nope::log::Warning) << err.what() << std::endl;
	}
    }
  Log(nope::log::Debug) << "Function feed over";
}

pythonpp::PythonFunction::~PythonFunction()
{
  Log(nope::log::Debug) << "Decrementing function '" << m_name << "'";
  Py_XDECREF(m_function);
}

pythonpp::PythonFunction::PythonFunction(PyObject *         module,
                                         std::string const &functionName)
    : m_function(nullptr), m_name(functionName)
{
  m_function = PyObject_GetAttrString(module, functionName.c_str());
  if (!m_function)
    throw(pythonpp::PyFunctionInitializationError("Function '" + functionName +
                                                  "' doesn't exist"));
  if (!PyCallable_Check(m_function))
    throw(pythonpp::PyFunctionInitializationError("Object '" + functionName +
                                                  "' is not callable"));
  Log(nope::log::Debug) << "Function '" << m_name << "' feeded!";
}

const std::string &pythonpp::PythonFunction::getName() const
{
  return m_name;
}