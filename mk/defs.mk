# Commands definitions
RM=		rm -f
RM_DIR=		rm -rf
ECHO=		printf
RANLIB=		ar rcs
CP=		cp
CHDIR=		cd
MKDIR=		mkdir

ROOT_DIR:=	$(realpath $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))/../)
INSTALL_DIR=	bin/
INSTALL_PATH=	$(ROOT_DIR)/$(INSTALL_DIR)
UNAME_S:=	$(shell uname -s)

# Compilation and link definitions
CXX=		clang++
CPP_VER=	c++1z

# Debug Infos
ifeq ($(DEBUG), yes)
CXXFLAGS=	-g -DDEBUG $(LOCAL_DEBUG_FLAGS)
LDFLAGS=	-g
else
CXXFLAGS=	-DNDEBUG
LDFLAGS=
endif

CXXFLAGS+=	$(addprefix -I, $(INC_DIR))	\
		$(LOCAL_COMP_FLAGS)

LDFLAGS+=	-lstdc++			\
		$(LOCAL_LINK_FLAGS)

ifeq ($(CXX),clang++)
CXXFLAGS+=	-std=$(CPP_VER) -W -Wall -Wextra -Weffc++
LDFLAGS+=
else ifeq ($(CXX),g++)
CXXFLAGS+=	-std=$(CPP_VER) -W -Wall -Wextra -Weffc++
LDFLAGS+=
else
CXXFLAGS+=
LDFLAGS+=
endif
