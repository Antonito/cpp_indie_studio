# Makefile dependencies directory
MK_DIR=		./mk/
MK_COMMON_DIR=	./../../../mk/

# Definitions for Makefile
NAME=		ini_test

LOCAL_COMP_FLAGS=

LOCAL_LINK_FLAGS= -L $(ROOT_DIR)/build/ -l indie_ini

LOCAL_DEBUG_FLAGS=

include $(MK_COMMON_DIR)colors.mk $(MK_COMMON_DIR)defs.mk

# Project's directories

SRC_DIR=	./

INCLUDE_DIR=	../include/

DIR_LIST=	$(SRC_DIR)

HEADER=

# Project's files

SRC_FILES=	main.cpp

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILES))

INC_DIR=	$(DIR_LIST:$(SRC_DIR)%=$(INCLUDE_DIR)%)

PRECOMPILED_HEADER= $(addprefix $(INCLUDE_DIR),$(HEADER))

# Rules
include $(MK_COMMON_DIR)rules.mk
