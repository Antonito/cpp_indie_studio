# Makefile dependencies directory
MK_DIR=		./mk/
MK_COMMON_DIR=	./../../../mk/

# Definitions for Makefile
NAME=			$(ROOT_DIR)/build/game_server

LOCAL_COMP_FLAGS=	-O2 -Wno-exit-time-destructors

LOCAL_LINK_FLAGS=	-L$(ROOT_DIR)/build/ -lindie_network -lindie_logger -lindie_multithread -lindie_packet -lindie_crypto -lindie_ini -lindie_exceptions

LOCAL_DEBUG_FLAGS=

include $(MK_COMMON_DIR)colors.mk $(MK_COMMON_DIR)defs.mk

# Project's directories

SRC_DIR=	./src/

INCLUDE_DIR=	./include/

DIR_LIST=	$(SRC_DIR)				\
		$(ROOT_DIR)/libs/network/include/	\
		$(ROOT_DIR)/libs/logger/include/	\
		$(ROOT_DIR)/libs/exceptions/include/	\
		$(ROOT_DIR)/libs/crypto/include/	\
		$(ROOT_DIR)/libs/ini/include/		\
		$(ROOT_DIR)/libs/packet/include/	\
		$(ROOT_DIR)/libs/serializer/include/

HEADER=		game_server_stdafx.hpp

# Project's files

SRC_FILES=	main.cpp		\
		GameServer.cpp		\
		GameServerCM.cpp	\
		GameServerTCP.cpp	\
		GameServerUDP.cpp	\
		Token.cpp		\
		GameClient.cpp		\
		GameLogic.cpp		\
		Config.cpp		\
		UDPClient.cpp

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILES))

INC_DIR=	$(DIR_LIST:$(SRC_DIR)%=$(INCLUDE_DIR)%)

PRECOMPILED_HEADER= $(addprefix $(INCLUDE_DIR),$(HEADER))

# Rules
ifeq ($(shell uname -s),Darwin)
include $(MK_COMMON_DIR)rules_osx.mk
else
include $(MK_COMMON_DIR)rules.mk
endif
