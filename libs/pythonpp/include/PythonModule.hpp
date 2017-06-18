//
// Created by brout_m on 03/05/17.
//

#ifndef CPP_INDIE_STUDIO_PYMODULE_HPP
# define CPP_INDIE_STUDIO_PYMODULE_HPP

# include <python2.7/Python.h>
# include <string>
# include <map>
# include <vector>
# include <memory>
# include <typeindex>
# include "PyFunctionReturnError.hpp"
# include "PyFunctionArgError.hpp"
# include "Logger.hpp"
# include "PythonLiteralConverter.hpp"
# include "apply.hpp"

namespace pythonpp
{
  class PythonFunction
  {
  public:
    explicit PythonFunction(PyObject *module, std::string const &functionName);
    ~PythonFunction();
    const std::string &getName() const;

    template <typename Ret, typename... Args>
    Ret exec(Args... args)
    {
      const std::int32_t  n{sizeof...(args)};
      std::tuple<Args...> tuple(args...);
      PyObject *          retValue{nullptr};
      PyObject *          pyArgs{nullptr};
      std::int32_t        index{0};
      Ret                 convertedRet;

      pyArgs = PyTuple_New(n);

      nope::log::Log(Debug) << "Parsing function '" << m_name << "' arguments...";
      nope::serialization::apply(tuple, [this, &index,
                                         &pyArgs](auto &e) -> bool {
	if (!PythonLiteralConverter::pushArgs<decltype(e)>(pyArgs, e, index))
	  throw(pythonpp::PyFunctionArgError(this->m_name));
	++index;
	return (true);
      });
      nope::log::Log(Debug) << "Parsing done.";

      retValue = PyObject_CallObject(m_function, pyArgs);
      Py_DECREF(pyArgs);
      if (!retValue)
	{
	  throw(pythonpp::PyFunctionReturnError(m_name));
	}

      nope::log::Log(Debug) << "Converting function '" << m_name << "' return...";
      convertedRet =
          std::move(PythonLiteralConverter::backConverter<Ret>(retValue));
      nope::log::Log(Debug) << "Convertion done.";
      Py_DECREF(retValue);
      return (convertedRet);
    }

  private:
    PyObject *  m_function;
    std::string m_name;

    PythonFunction(PythonFunction const &) = delete;
    PythonFunction operator=(PythonFunction const &) = delete;
  };

  class PythonModule
  {
  public:
    explicit PythonModule(std::string const &moduleName);
    ~PythonModule();
    PyObject *ptr();
    void feedFunctions(std::vector<std::string> const &functionNames);

    template <typename Ret, typename... Args>
    bool exec(std::size_t const index, Ret &out, Args... args)
    {
      try
	{
	  nope::log::Log(Debug) << "Executing '"
	                        << m_functions[index]->getName() << "'...";
	  out = m_functions[index]->exec<Ret, Args...>(args...);
          nope::log::Log(Debug) << "Execution of '"
                                << m_functions[index]->getName() << "' done.";
	}
      catch (indie::AException &err)
	{
          nope::log::Log(Warning) << err.what() << std::endl;
	  return (false);
	}
      return (true);
    }

  private:
    PyObject *                                   m_module;
    std::vector<std::unique_ptr<PythonFunction>> m_functions;
    std::string const &                          m_moduleName;
    PythonModule(PythonModule const &) = delete;
    PythonModule &operator=(PythonModule const &) = delete;
  };
}
#endif // CPP_INDIE_STUDIO_PYMODULE_HPP
