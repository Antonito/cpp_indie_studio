//
// Created by brout_m on 09/05/17.
//

#include <PythonLiteralConverter.hpp>

namespace pythonpp
{
  template <>
  bool PythonLiteralConverter::pushArgs<bool>(PyObject *args, bool arg,
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
  bool PythonLiteralConverter::pushArgs<int>(PyObject *args, int arg, int pos)
  {
    PyObject *l_arg;

    l_arg = PyInt_FromLong(arg);
    if (!l_arg)
      return (false);
    PyTuple_SetItem(args, pos, l_arg);
    return (true);
  }

  template <>
  bool PythonLiteralConverter::pushArgs<std::string &>(PyObject *   args,
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
  int PythonLiteralConverter::backConverter(PyObject *value)
  {
    return (static_cast<int>(PyInt_AsLong(value)));
  }

  template <>
  std::string PythonLiteralConverter::backConverter(PyObject *value)
  {
    std::string store(PyString_AsString(value));
    return (store);
  }
}