// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef PACKET_STDAFX_HPP_
#define PACKET_STDAFX_HPP_

#include "packet_targetver.h"

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers

// Reference additional headers your program requires here

#include <iostream>
#include <iomanip>
#include <fstream>
#include <memory>
#include "ISerializable.hpp"
#include "PacketHeader.hpp"
#include "Packet.hpp"
#include "GameServerCMPacket.hpp"
#include "GameClientCMPacket.hpp"

#endif // !PACKET_STDAFX_HPP_
