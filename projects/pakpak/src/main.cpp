#include "AppLauncher.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32

#define WIN32_LEAN_AND_MEAN

#include "windows.h"

#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)

#else

int main(int argc, char *argv[])

#endif

{

  AppLauncher app;

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
