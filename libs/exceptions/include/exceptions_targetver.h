#ifndef EXCEPTIONS_TARGETVER_H_
#define EXCEPTIONS_TARGETVER_H_

// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform,
// include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before
// including SDKDDKVer.h.

#if defined(_WIN32) && !defined(__on__linux__)
#include <SDKDDKVer.h>
#endif

#endif // !EXCEPTIONS_TARGETVER_H_
