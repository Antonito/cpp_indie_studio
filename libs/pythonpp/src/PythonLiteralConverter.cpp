//
// Created by brout_m on 09/05/17.
//

#include <iostream>
#include "PythonLiteralConverter.hpp"

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

    std::cout << "pushing arg : " << arg << " at pos " << pos << std::endl;
    l_arg = PyInt_FromLong(arg);
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
}