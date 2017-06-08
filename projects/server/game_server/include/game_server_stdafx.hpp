// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef GAME_SERVER_STDAFX_HPP_
#define GAME_SERVER_STDAFX_HPP_

#include "game_server_targetver.h"

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers

// Reference additional headers your program requires here

#include <cassert>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <memory>
#include <vector>
#include <cstring>
#include <algorithm>
#include "Logger.hpp"
#include "GameServer.hpp"
#include "TCPSocket.hpp"
#include "Packet.hpp"
#include "GameServerCMPacket.hpp"
#include "Token.hpp"
#include "Ini.hpp"
#include "Config.hpp"
#include "GameClient.hpp"
#include "json.hpp"

#endif // !GAME_SERVER_STDAFX_HPP_
