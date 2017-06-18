# Makefile dependencies directory
MK_DIR=		./mk/
MK_COMMON_DIR=	./../../mk/

# Definitions for Makefile
NAME=		$(ROOT_DIR)/pakpak

LOCAL_COMP_FLAGS=

LOCAL_LINK_FLAGS= 	-l OIS -l OgreMain -l boost_system 	\
			-L $(ROOT_DIR)/build/ -l indie_logger 	\
			-l CEGUIBase-0 -l CEGUIOgreRenderer-0 	\
			-l indie_network -lindie_ini		\
			-l indie_packet				\
			-l indie_crypto -l sndfile		\
			-l indie_exceptions			\
			-l BulletDynamics -l BulletCollision	\
			-l OgreBulletDynamics			\
			-l OgreBulletCollisions			\
			-l LinearMath

ifeq ($(shell uname -s),Darwin)
LOCAL_COMP_FLAGS+=	-x objective-c++
LOCAL_LINK_FLAGS+=	-ObjC++ -framework Cocoa -framework Carbon -framework OpenAL
else
LOCAL_LINK_FLAGS+=	-lopenal
endif

LOCAL_DEBUG_FLAGS=

include $(MK_COMMON_DIR)colors.mk $(MK_COMMON_DIR)defs.mk

ifeq ($(CXX), clang++)
CXXFLAGS+=		-Wno-global-constructors	\
			-Wno-exit-time-destructors	\
			-Wno-weak-vtables		\
			-Wno-padded			\
			-Wno-switch-enum
endif

# Project's directories

SRC_DIR=	./src/

GAME_DIR=	$(SRC_DIR)game/

GAME_LAYER_DIR=	$(GAME_DIR)layer/

GAME_CAR_DIR=	$(GAME_DIR)car/

GAME_MAP_DIR=	$(GAME_DIR)map/

GAME_TOOLS_DIR=	$(GAME_DIR)tools/

GAME_MENU_DIR=  $(GAME_DIR)menu/

NETWORK_DIR=	$(SRC_DIR)network/

INCLUDE_DIR=	./include/

DIR_LIST=	$(SRC_DIR)		\
		$(GAME_DIR)		\
		$(GAME_LAYER_DIR)	\
		$(GAME_CAR_DIR)		\
		$(GAME_TOOLS_DIR)	\
		$(GAME_MAP_DIR)     	\
	        $(GAME_MENU_DIR)	\
		$(NETWORK_DIR)

ifeq ($(shell uname -s),Darwin)
HEADER=
else
HEADER=		pakpak_stdafx.hpp
endif

# Project's files


SRC_FILES=		main.cpp			\
			AppLauncher.cpp			\
			InputListener.cpp		\
			AContext.cpp			\
			ContextGame.cpp			\
			SettingsPlayer.cpp		\
			SoundManager.cpp		\
			SaveData.cpp			\
			ContextSplash.cpp		\
			Config.cpp

GAME_FILES=		GameData.cpp			\
			LocalPlayer.cpp			\
			PlayerData.cpp

GAME_LAYER_FILES=	ALayer.cpp			\
			Chat.cpp			\
			GameGUI.cpp			\
			InGame.cpp			\
			Loading.cpp			\
			Menu.cpp			\
			PostGame.cpp			\
			PreGame.cpp			\
			Score.cpp			\
			SpecGUI.cpp			\
			Spectator.cpp			\
			HUD.cpp				\
			Pauser.cpp

GAME_CAR_FILES=		ACar.cpp			\
			EmptyCar.cpp

GAME_MAP_FILES=		Map.cpp				\
			PathPoint.cpp

GAME_TOOLS_FILES=	Tools.cpp

GAME_MENU_FILES=    	GUI.cpp				\
			MainMenu.cpp			\
			ContextMenu.cpp			\
			MenuManager.cpp     		\
			MenuOptions.cpp 		\
			MenuKeymap.cpp 			\
			MenuSolo.cpp 			\
			MenuMultiplayer.cpp 		\
			AssetSetter.cpp			\
			MenuScores.cpp			\
			InGameHUD.cpp			\
			InGamePause.cpp			\
			AssetResizer.cpp		\
			Dim.cpp

NETWORK_FILES=		NetworkManager.cpp		\
			NetworkAuth.cpp			\
			NetworkGameServer.cpp		\
			NetworkConnect.cpp		\
			NetworkGame.cpp

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILES))			\
		$(addprefix $(GAME_DIR), $(GAME_FILES))			\
		$(addprefix $(GAME_LAYER_DIR), $(GAME_LAYER_FILES))	\
		$(addprefix $(GAME_CAR_DIR), $(GAME_CAR_FILES))		\
		$(addprefix $(GAME_TOOLS_DIR), $(GAME_TOOLS_FILES))	\
		$(addprefix $(GAME_MAP_DIR), $(GAME_MAP_FILES))     	\
		$(addprefix $(GAME_MENU_DIR), $(GAME_MENU_FILES))	\
		$(addprefix $(NETWORK_DIR), $(NETWORK_FILES))


INC_DIR=	$(DIR_LIST:$(SRC_DIR)%=$(INCLUDE_DIR)%)			\
		$(ROOT_DIR)/libs/serializer/include/			\
		$(ROOT_DIR)/libs/logger/include/			\
		$(ROOT_DIR)/libs/exceptions/include/			\
		$(ROOT_DIR)/libs/crypto/include/			\
		$(ROOT_DIR)/libs/network/include/			\
		$(ROOT_DIR)/libs/packet/include/			\
		$(ROOT_DIR)/libs/ini/include/				\
		/usr/include/OgreBullet/Dynamics 			\
		/usr/include/OgreBullet/Collisions 			\
		/usr/local/include/OgreBullet/Dynamics 			\
		/usr/local/include/OgreBullet/Collisions 		\
		/usr/include/bullet					\
		/usr/local/include/bullet				\
		/usr/include/OGRE					\
		/usr/local/include/OGRE					\
		/usr/local/include/OGRE/RenderSystems/GL/		\
		/usr/local/include/OGRE/RenderSystems/GL/OSX

PRECOMPILED_HEADER= $(addprefix $(INCLUDE_DIR),$(HEADER))

# Rules
include $(MK_COMMON_DIR)rules.mk
