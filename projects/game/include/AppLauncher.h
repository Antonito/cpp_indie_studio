#ifndef APPLAUNCHER_H_
#define APPLAUNCHER_H_

#include <memory>
#include <Ogre.h>
#include "InputListener.h"

class AppLauncher

{

public:
  AppLauncher();

  ~AppLauncher();

  bool start();

private:
  std::unique_ptr<Ogre::Root>         mRoot;
  std::unique_ptr<Ogre::RenderWindow> mWindow;
  std::unique_ptr<Ogre::SceneManager> mSceneMgr;
  std::unique_ptr<Ogre::Camera>       mCamera;
  std::unique_ptr<InputListener>      mInputListener
};

#endif // !APPLAUNCHER_H_