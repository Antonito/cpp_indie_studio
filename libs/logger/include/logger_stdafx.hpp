// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "logger_targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// Reference additional headers your program requires here

#include <iostream>
#include <iomanip>
#include <fstream>
#include <memory>
#include "LogMessage.hpp"
#include "LogSink.hpp"
#include "Logger.hpp"