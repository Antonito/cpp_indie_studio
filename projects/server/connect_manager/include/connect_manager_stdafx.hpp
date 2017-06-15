// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef CONNECT_MANAGER_STDAFX_HPP_
#define CONNECT_MANAGER_STDAFX_HPP_

#include "connect_manager_targetver.h"

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers

// Reference additional headers your program requires here

#include <cassert>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <memory>
#include <vector>
#include <array>
#include <thread>
#include <string>
#include <condition_variable>
#include <algorithm>
#include <mutex>
#include <algorithm>
#if defined(__linux__) || defined(__APPLE__)
#include <sys/select.h>
#endif
#include "LicenseServer.hpp"
#include "GameClientServer.hpp"
#include "GameClient.hpp"
#include "Logger.hpp"
#include "SockError.hpp"
#include "Queue.hpp"
#include "ResultGetter.hpp"
#include "RequestToken.hpp"
#include "Ini.hpp"

#endif // !CONNECT_MANAGER_STDAFX_HPP_
