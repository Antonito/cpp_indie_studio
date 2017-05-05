#ifndef APPLAUNCHER_H_
#define APPLAUNCHER_H_

#include <memory>
#include <OGRE/Ogre.h>
#include "InputListener.h"

class AppLauncher

{

public:
  AppLauncher();

  ~AppLauncher();

  bool start();

  void createFrameListener();

private:
  std::unique_ptr<Ogre::Root>         mRoot;
  std::unique_ptr<Ogre::RenderWindow> mWindow;
  Ogre::SceneManager *                mSceneMgr;
  std::unique_ptr<Ogre::Camera>       mCamera;
  std::unique_ptr<InputListener>      mInputListener;
};

#endif // !APPLAUNCHER_H_