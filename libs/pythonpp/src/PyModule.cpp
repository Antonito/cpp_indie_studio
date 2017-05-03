//
// Created by brout_m on 03/05/17.
//

#include "PyModule.hpp"

pythonpp::PyModule::~PyModule()
{
  Py_DecRef(m_name);
  Py_DecRef(m_module);
  Py_DecRef(m_dict);
}

pythonpp::PyModule::PyModule(const std::string &moduleName)
    : m_name(nullptr), m_module(nullptr), m_dict(nullptr)
{
    Py_Initialize();
    if (!Py_IsInitialized())
}
