// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef LOGGER_STDAFX_HPP_
#define LOGGER_STDAFX_HPP_

#include "logger_targetver.h"

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers

// Reference additional headers your program requires here

#include <iostream>
#include <iomanip>
#include <fstream>
#include <memory>
#include "LogMessage.hpp"
#include "LogSink.hpp"
#include "Logger.hpp"

#endif // !LOGGER_STDAFX_HPP_
