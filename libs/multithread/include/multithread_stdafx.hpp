// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef MULTITHREAD_STDAFX_HPP_
#define MULTITHREAD_STDAFX_HPP_

#include "multithread_targetver.h"

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers

// Reference additional headers your program requires here

#include <mutex>
#include <condition_variable>
#include "Semaphore.hpp"

#endif // !MULTITHREAD_STDAFX_HPP_
