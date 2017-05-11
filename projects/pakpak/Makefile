# Makefile dependencies directory
MK_DIR=		./mk/
MK_COMMON_DIR=	./../../mk/

# Definitions for Makefile
NAME=		$(ROOT_DIR)/pakpak

LOCAL_COMP_FLAGS= -Wno-global-constructors -Wno-exit-time-destructors

LOCAL_LINK_FLAGS= -l OIS -l OgreMain -l boost_system

LOCAL_DEBUG_FLAGS=

include $(MK_COMMON_DIR)colors.mk $(MK_COMMON_DIR)defs.mk

# Project's directories

SRC_DIR=	./src/

INCLUDE_DIR=	./include/

DIR_LIST=	$(SRC_DIR)

HEADER=		

# Project's files

SRC_FILES=	main.cpp			\
		AppLauncher.cpp			\
		InputListener.cpp		\
		AContext.cpp			\
		ContextGame.cpp			\
		ContextMenu.cpp			\
		ContextSplash.cpp

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILES))

INC_DIR=	$(DIR_LIST:$(SRC_DIR)%=$(INCLUDE_DIR)%)

PRECOMPILED_HEADER= $(addprefix $(INCLUDE_DIR),$(HEADER))

# Rules
include $(MK_COMMON_DIR)rules.mk
