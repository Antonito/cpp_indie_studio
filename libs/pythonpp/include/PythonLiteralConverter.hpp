//
// Created by brout_m on 05/05/17.
//

#ifndef PYTHONLITERALCONVERTER_HPP
#define PYTHONLITERALCONVERTER_HPP

#include <python2.7/Python.h>
#include <string>
#include <iostream>

namespace pythonpp
{
  class PythonLiteralConverter
  {
  public:
    template <typename T>
    static bool pushArgs(PyObject *args, T arg, int pos)
    {
      PyObject *l_arg;

      l_arg = PyLong_FromLong(arg);
      if (!l_arg)
	return (false);
      PyTuple_SetItem(args, pos, l_arg);
      return (true);
    }

    template <typename Ret>
    static Ret backConverter(PyObject *value)
    {
      return (static_cast<Ret>(PyLong_AsLong(value)));
    }
  };

  template <>
  inline bool PythonLiteralConverter::pushArgs<std::string &>(PyObject *args,
                                                              std::string &arg,
                                                              int          pos)
  {
    PyObject *l_arg;

    l_arg = PyString_FromString(arg.c_str());
    if (!l_arg)
      return (false);
    PyTuple_SetItem(args, pos, l_arg);
    return (true);
  }

  template <>
  inline bool PythonLiteralConverter::pushArgs<bool>(PyObject *args, bool arg,
                                                     int pos)
  {
    PyObject *l_arg;

    l_arg = PyBool_FromLong(arg);
    if (!l_arg)
      return (false);
    PyTuple_SetItem(args, pos, l_arg);
    return (true);
  }

  template <>
  inline bool PythonLiteralConverter::pushArgs<double>(PyObject *args,
                                                       double arg, int pos)
  {
    PyObject *l_arg;

    l_arg = PyFloat_FromDouble(arg);
    if (!l_arg)
      return (false);
    PyTuple_SetItem(args, pos, l_arg);
    return (true);
  }

  template <>
  inline bool PythonLiteralConverter::pushArgs<int>(PyObject *args, int arg,
                                                    int pos)
  {
    PyObject *l_arg;

    l_arg = PyInt_FromLong(arg);
    if (!l_arg)
      return (false);
    PyTuple_SetItem(args, pos, l_arg);
    return (true);
  }

  template <>
  inline int PythonLiteralConverter::backConverter(PyObject *value)
  {
    return (static_cast<int>(PyInt_AsLong(value)));
  }

  template <>
  inline std::string PythonLiteralConverter::backConverter(PyObject *value)
  {
    std::string store(PyString_AsString(value));
    return (store);
  }

  template <>
  inline double PythonLiteralConverter::backConverter(PyObject *value)
  {
    return (PyFloat_AsDouble(value));
  }
}

#endif // CPP_PLAZZA_PYTHONLITERALCONVERTER_HPP
