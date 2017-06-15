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
#include "AppLauncher.hpp"
#include "binary.hpp"
#include "ContextGame.hpp"
#include "ContextMenu.hpp"
#include "ContextSplash.hpp"
#include "GameState.hpp"
#include "InputListener.hpp"

// Game
#include "AContext.hpp"
#include "CameraMode.hpp"
#include "GameData.hpp"
#include "LocalPlayer.hpp"
#include "PlayerData.hpp"

// Game.Car
#include "ACar.hpp"
#include "EmptyCar.hpp"

// Game.Layer
#include "ALayer.hpp"
#include "Chat.hpp"
#include "GameGUI.hpp"
#include "InGame.hpp"
#include "Loading.hpp"
#include "Menu.hpp"
#include "PostGame.hpp"
#include "PreGame.hpp"
#include "Score.hpp"
#include "SpecGUI.hpp"
#include "Spectator.hpp"

// Game.Map
#include "Map.hpp"
#include "PathPoint.hpp"

//
// Logger
//
#include "Logger.hpp"

//
// Physic
//

// Disable clang warning for templated class padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

#include <Shapes/OgreBulletCollisionsBoxShape.h>
#include <Shapes/OgreBulletCollisionsSphereShape.h>
#include <Shapes/OgreBulletCollisionsTrimeshShape.h>
#include <Shapes/OgreBulletCollisionsConvexHullShape.h>
#include "Tools.hpp"

// Disable clang warning for templated class padding
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !PAKPAK_STDAFX_HPP_
