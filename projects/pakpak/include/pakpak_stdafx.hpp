// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef PAKPAK_STDAFX_HPP_
#define PAKPAK_STDAFX_HPP_

#ifdef _WIN32
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#endif                      // !_WIN32

// TODO: reference additional headers your program requires here

//
// Ogre
//
#include <OGRE/OgreException.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreLight.h>
#include <OGRE/OgreCamera.h>
#include <OGRE/OgreViewport.h>

//
// OIS
//
#include <OIS/OIS.h>

//
// Windows
//
#ifdef _WIN32
#include "windows.h"
#endif // !_WIN32

//
// Utils
//
#include <cassert>

//
// Project headers
//
#include "AContext.hpp"
#include "AppLauncher.hpp"
#include "CameraMode.hpp"
#include "ContextGame.hpp"
#include "ContextMenu.hpp"
#include "ContextSplash.hpp"
#include "GameData.hpp"
#include "GameState.hpp"
#include "InGame.hpp"
#include "InputListener.hpp"
#include "LocalPlayer.hpp"
#include "Loading.hpp"
#include "PlayerData.hpp"
#include "PostGame.hpp"
#include "PreGame.hpp"

#endif // !PAKPAK_STDAFX_HPP_
