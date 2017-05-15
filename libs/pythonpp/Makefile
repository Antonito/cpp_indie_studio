# Makefile dependencies directory
1;2802;0cMK_DIR=		./mk/
MK_COMMON_DIR=	./../../mk/

# Definitions for Makefile
NAME=		$(ROOT_DIR)/build/libindie_pythonmodule

LOCAL_COMP_FLAGS=	-O2 -g3 -Wno-unused-variable

LOCAL_LINK_FLAGS= 	-lpython2.7 -L../../build -lindie_logger -lindie_exceptions

LOCAL_DEBUG_FLAGS=

include $(MK_COMMON_DIR)colors.mk $(MK_COMMON_DIR)defs.mk

# Project's directories

SRC_DIR=	./src/

INCLUDE_DIR=	./include/ 				\
		$(ROOT_DIR)/libs/logger/include 	\
		$(ROOT_DIR)/libs/exceptions/include 	\
		$(ROOT_DIR)/libs/serializer/include

DIR_LIST=	$(SRC_DIR)

HEADER=

# Project's files

SRC_FILES=	PythonModule.cpp \
		PythonLiteralConverter.cpp \
		main-test.cpp

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILES))

INC_DIR=	$(DIR_LIST:$(SRC_DIR)%=$(INCLUDE_DIR)%)

PRECOMPILED_HEADER= $(addprefix $(INCLUDE_DIR),$(HEADER))

# Rules
include $(MK_COMMON_DIR)rules.mk
