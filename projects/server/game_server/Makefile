# Makefile dependencies directory
MK_DIR=		./mk/
MK_COMMON_DIR=	./../../../mk/

# Definitions for Makefile
NAME=			$(ROOT_DIR)/build/game_server

LOCAL_COMP_FLAGS=	-O2

LOCAL_LINK_FLAGS=	-L$(ROOT_DIR)/build/ -lindie_network -lindie_logger -lindie_exceptions -lindie_multithread -lindie_packet -lindie_crypto

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
		$(ROOT_DIR)/libs/packet/include/

HEADER=		game_server_stdafx.hpp

# Project's files

SRC_FILES=	main.cpp	\
		GameServer.cpp	\
		Token.cpp	\
		GameClient.cpp

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILES))

INC_DIR=	$(DIR_LIST:$(SRC_DIR)%=$(INCLUDE_DIR)%)

PRECOMPILED_HEADER= $(addprefix $(INCLUDE_DIR),$(HEADER))

# Rules
include $(MK_COMMON_DIR)rules.mk
