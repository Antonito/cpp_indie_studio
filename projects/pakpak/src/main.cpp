#include "pakpak_stdafx.hpp"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)

#else

int main(int, char **)

#endif

{
  nope::log::Logger::start("nope.log");
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
