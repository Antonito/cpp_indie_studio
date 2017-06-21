# Makefile dependencies directory
MK_DIR=		./mk/
MK_COMMON_DIR=	./../../mk/

# Definitions for Makefile
NAME=		$(ROOT_DIR)/build/libindie_logger.a

LOCAL_COMP_FLAGS= -Wno-global-constructors -Wno-exit-time-destructors

LOCAL_LINK_FLAGS=

LOCAL_DEBUG_FLAGS=

include $(MK_COMMON_DIR)colors.mk $(MK_COMMON_DIR)defs.mk

# Project's directories

SRC_DIR=	./src/

INCLUDE_DIR=	./include/

DIR_LIST=	$(SRC_DIR)

HEADER=		logger_stdafx.hpp

# Project's files

SRC_FILES=	LogMessage.cpp			\
		LogSink.cpp			\
		Logger.cpp

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILES))

INC_DIR=	$(DIR_LIST:$(SRC_DIR)%=$(INCLUDE_DIR)%)

PRECOMPILED_HEADER= $(addprefix $(INCLUDE_DIR),$(HEADER))

# Rules
ifeq ($(shell uname -s),Darwin)
include $(MK_COMMON_DIR)rules_osx.mk
else
include $(MK_COMMON_DIR)rules.mk
endif
