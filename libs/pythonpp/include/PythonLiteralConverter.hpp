//
// Created by brout_m on 05/05/17.
//

#ifndef PYTHONLITERALCONVERTER_HPP
#define PYTHONLITERALCONVERTER_HPP

#include <python2.7/Python.h>
#include <string>

namespace pythonpp {
  class PythonLiteralConverter {
  public:
    template<typename T>
    static bool pushArgs(PyObject *args, T arg, int pos) {
      PyObject *l_arg;

      l_arg = PyLong_FromLong(arg);
      if (!l_arg)
        return (false);
      PyTuple_SetItem(args, pos, l_arg);
      return (true);
    }

    template<typename Ret>
    static Ret backConverter(PyObject *value) {
      return (static_cast<Ret>(PyLong_AsLong(value)));
    }
  };
}
#endif // CPP_PLAZZA_PYTHONLITERALCONVERTER_HPP
