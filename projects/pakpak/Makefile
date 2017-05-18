# Makefile dependencies directory
MK_DIR=		./mk/
MK_COMMON_DIR=	./../../mk/

# Definitions for Makefile
NAME=		$(ROOT_DIR)/pakpak

LOCAL_COMP_FLAGS=
ifeq ($(CXX), clang++)
LOCAL_COMP_FLAGS+=	-Wno-global-constructors		\
			-Wno-exit-time-destructors		\
			-Wno-weak-vtables			\
			-Wno-padded
endif

LOCAL_LINK_FLAGS= -l OIS -l OgreMain -l boost_system

LOCAL_DEBUG_FLAGS=

include $(MK_COMMON_DIR)colors.mk $(MK_COMMON_DIR)defs.mk

# Project's directories

SRC_DIR=	./src/

GAME_DIR=	$(SRC_DIR)game/

GAME_LAYER_DIR=	$(GAME_DIR)layer/

GAME_CAR_DIR=	$(GAME_DIR)car/

INCLUDE_DIR=	./include/

DIR_LIST=	$(SRC_DIR)		\
		$(GAME_DIR)		\
		$(GAME_LAYER_DIR)	\
		$(GAME_CAR_DIR)

HEADER=		pakpak_stdafx.hpp

# Project's files


SRC_FILES=		main.cpp			\
			AppLauncher.cpp			\
			InputListener.cpp		\
			AContext.cpp			\
			ContextGame.cpp			\
			ContextMenu.cpp			\
			ContextSplash.cpp

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
			Spectator.cpp

GAME_CAR_FILES=		ACar.cpp			\
			EmptyCar.cpp

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILES))			\
		$(addprefix $(GAME_DIR), $(GAME_FILES))			\
		$(addprefix $(GAME_LAYER_DIR), $(GAME_LAYER_FILES))	\
		$(addprefix $(GAME_CAR_DIR), $(GAME_CAR_FILES))

INC_DIR=	$(DIR_LIST:$(SRC_DIR)%=$(INCLUDE_DIR)%)

PRECOMPILED_HEADER= $(addprefix $(INCLUDE_DIR),$(HEADER))

# Rules
include $(MK_COMMON_DIR)rules.mk
