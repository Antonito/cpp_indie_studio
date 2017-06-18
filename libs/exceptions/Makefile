# Makefile dependencies directory
MK_DIR=		./mk/
MK_COMMON_DIR=	./../../mk/

# Definitions for Makefile
NAME=		$(ROOT_DIR)/build/libindie_exceptions.a

LOCAL_COMP_FLAGS=	-O2

LOCAL_LINK_FLAGS=

LOCAL_DEBUG_FLAGS=

include $(MK_COMMON_DIR)colors.mk $(MK_COMMON_DIR)defs.mk

# Project's directories

SRC_DIR=	./src/

INCLUDE_DIR=	./include/

DIR_LIST=	$(SRC_DIR)

HEADER=		exceptions_stdafx.hpp

# Project's files

SRC_FILES=	AException.cpp				\
		IOError.cpp				\
		SockError.cpp 				\
		PyInitializationError.cpp 		\
		PyFunctionArgError.cpp			\
		PyFunctionReturnError.cpp		\
		PyFunctionInitializationError.cpp	\

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILES))

INC_DIR=	$(DIR_LIST:$(SRC_DIR)%=$(INCLUDE_DIR)%)

PRECOMPILED_HEADER= $(addprefix $(INCLUDE_DIR),$(HEADER))

# Rules
include $(MK_COMMON_DIR)rules.mk
