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
#if defined __APPLE__
#include <ois/OIS.h>
#else
#include <OIS/OIS.h>
#endif

//
// Windows
//
#ifdef _WIN32
#include "windows.h"
#include <io.h>
#endif // !_WIN32

//
// Utils
//
#include <functional>
#include <cassert>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstring>

//
// Project headers
//
#include "AppLauncher.hpp"
#include "binary.hpp"
#include "json.hpp"
#include "ContextGame.hpp"
#include "game/menu/ContextMenu.hpp"
#include "ContextSplash.hpp"
#include "GameState.hpp"
#include "InputListener.hpp"
#include "SettingsPlayer.hpp"
#include "SoundManager.hpp"
#include "SaveData.hpp"

// Menu
#include "AssetSetter.hpp"
#include "ContextMenu.hpp"
#include "GUI.hpp"
#include "IMenuLayer.hpp"
#include "InGameHUD.hpp"
#include "InGamePause.hpp"
#include "MainMenu.hpp"
#include "MenuKeymap.hpp"
#include "MenuManager.hpp"
#include "MenuMultiplayer.hpp"
#include "MenuOptions.hpp"
#include "MenuScores.hpp"
#include "MenuSolo.hpp"
#include "game/menu/AssetResizer.hpp"
#include "game/menu/Dim.hpp"

// Game
#include "Pauser.hpp"
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
#include "tinyxml.h"
#include "CheckPoint.hpp"

//
// Logger
//
#include "Logger.hpp"
#include "IOError.hpp"

// Network
#include "NetworkManager.hpp"
#include "NetworkGameServer.hpp"
//
// Sound
//
#include "SoundManager.hpp"

//
// Physic
//

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang            system_header
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Woverloaded-virtual"
#endif

#include <Shapes/OgreBulletCollisionsBoxShape.h>
#include <Shapes/OgreBulletCollisionsSphereShape.h>
#include <Shapes/OgreBulletCollisionsTrimeshShape.h>
#include <Shapes/OgreBulletCollisionsConvexHullShape.h>
#include "Tools.hpp"

// Disable clang warning for templated class padding
#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#endif // !PAKPAK_STDAFX_HPP_
