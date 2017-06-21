#include "pakpak_stdafx.hpp"
#if defined __APPLE__

// Disable lib errors
#if defined   __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#import <Cocoa/Cocoa.h>
#ifndef __glew_h__
#define __glew_h__
#endif
#include "OSX/macUtils.h"
#import "OSXPort.h"

// Reset flags
#if defined   __clang__
#pragma clang diagnostic pop
#endif

#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)

#else

int main(int, char **)

#endif

{
  nope::log::Logger::start("pakpak_racing.log");
  nope::log::Logger::logLevel = nope::log::LogLevel::LOG_DEBUG;
  core::AppLauncher app;

  try
    {

      app.start();
    }
  catch (Ogre::Exception &e)
    {

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32

      MessageBox(NULL, e.getFullDescription().c_str(),
                 "An exception has occured!",
                 MB_OK | MB_ICONERROR | MB_TASKMODAL);

#else

      std::cerr << "An exception has occured: " <<

          e.getFullDescription().c_str() << std::endl;

#endif
    }
  return 0;
}
