//
// Created by brout_m on 03/05/17.
//

#include <PyFunctionInitializationError.hpp>
#include "PyModule.hpp"
#include "PyInitializationError.hpp"
#include "PyFunctionInitializationError.hpp"
#include "Logger.hpp"

pythonpp::PyModule::~PyModule()
{
  Py_DECREF(m_module);
}

pythonpp::PyModule::PyModule(std::string const &moduleName)
    : m_module(nullptr), m_functions({})
{
  PyObject *name;

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

PyObject *pythonpp::PyModule::ptr()
{
  return m_module;
}

void pythonpp::PyModule::feedFunctions(std::vector<std::string> &functionNames)
{
  for (std::string &name : functionNames)
    {
      m_functions.erase(name);
      try
	{
	  m_functions[name] = std::make_unique<PyFunction>(*this, name);
	}
      catch (pythonpp::PyFunctionInitializationError &err)
	{
	  nope::log::Log(nope::log::Warning) << err << std::endl;
	}
    }
}

pythonpp::PyModule::PyFunction::~PyFunction()
{
  Py_XDECREF(m_function);
}

pythonpp::PyModule::PyFunction::PyFunction(pythonpp::PyModule &module,
                                           std::string const & functionName)
    : m_function(nullptr)
{
  m_function = PyObject_GetAttrString(module.ptr(), functionName.c_str());
  if (!m_function)
    throw(pythonpp::PyFunctionInitializationError("Function '" + functionName +
                                                  "' doesn't exist"));
  if (!PyCallable_Check(m_function))
    throw(pythonpp::PyFunctionInitializationError("Object '" + functionName +
                                                  "' is not callable"));
}