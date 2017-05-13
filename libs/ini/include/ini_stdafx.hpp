// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef INI_STDAFX_HPP_
#define INI_STDAFX_HPP_

#ifdef _WIN32
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers

#endif // !_WIN32

// TODO: reference additional headers your program requires here
#include <fstream>
#include <cctype>

#include "Section.hpp"
#include "Ini.hpp"

#endif // !INI_STDAFX_HPP_
