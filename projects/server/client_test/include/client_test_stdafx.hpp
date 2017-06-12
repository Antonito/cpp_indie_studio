// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef CLIENT_TEST_STDAFX_HPP_
#define CLIENT_TEST_STDAFX_HPP_

#include "client_test_targetver.h"

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers

// Reference additional headers your program requires here

#ifdef _WIN32
#include <Windows.h>
#endif

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
#include <cstdlib>
#include <algorithm>
#include "Logger.hpp"
#include "TCPSocket.hpp"
#include "SockError.hpp"
#include "Packet.hpp"
#include "GameClientCMPacket.hpp"
#include "GameClientGSPacket.hpp"
#include "IClient.hpp"
#include "Ini.hpp"
#include "json.hpp"
#include "Config.hpp"
#include "Hash.hpp"

#if defined(_WIN32)
#include "dirent/dirent.h"
#else
#include <dirent.h>
#endif

#endif // !CLIENT_TEST_STDAFX_HPP_
