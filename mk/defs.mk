# Commands definitions
RM=		rm -f
RM_DIR=		rm -rf
RM_EMPTY_DIR=	rm -d
ECHO=		printf
RANLIB=		ar rcs
CP=		cp
CHDIR=		cd
MKDIR=		mkdir

ROOT_DIR:=	$(realpath $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))/../)
INSTALL_DIR=	bin/
INSTALL_PATH=	$(ROOT_DIR)/$(INSTALL_DIR)
UNAME_S:=	$(shell uname -s)

TARGET=		native

# Compilation and link definitions
CXX=		g++
CPP_VER=	c++14

# Simple OSX check
ifeq ($(UNAME_S),Darwin)
CXX=		clang++
endif

# Check taget
ifeq ($(TARGET), WIN32)
CXX=		i686-w64-mingw32-g++ -D__on__linux__
else ifeq ($(TARGET), WIN64)
CXX=		x86_64-w64-mingw32-g++ -D__on__linux__
endif

# Debug Infos
ifeq ($(DEBUG), yes)
CXXFLAGS=	-g -DDEBUG -O0 $(LOCAL_DEBUG_FLAGS)
LDFLAGS=	-g -rdynamic -fsanitize=undefined -fsanitize=address
else
CXXFLAGS=	-DNDEBUG -fomit-frame-pointer -march=native
LDFLAGS=	-s -Wl,-O1
endif

CXXFLAGS+=	-std=$(CPP_VER) -W -Wall -Wextra -Weffc++  -Wcomment 		\
		-Wmain -Wpointer-arith -Wreturn-type -Wstrict-aliasing 		\
		-Wtrigraphs -Wuninitialized -Wunknown-pragmas 			\
		-Wcomment -Wconversion -Wcast-align 				\
		-pedantic -pipe -fstack-protector -Wformat-nonliteral		\
		-Wnon-virtual-dtor -Wreorder -Wenum-compare			\
		-Winvalid-pch -Woverloaded-virtual -Wabi			\
		$(addprefix -I, $(INC_DIR))					\
		$(LOCAL_COMP_FLAGS)

LDFLAGS+=	-fuse-ld=gold -Wl,--fatal-warnings -lstdc++			\
		$(LOCAL_LINK_FLAGS)

ifeq ($(CXX),clang++)
CXXFLAGS+=	-Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic 	\
		-Wno-c++11-compat
LDFLAGS+=
else ifeq ($(CXX),g++)
CXXFLAGS+=	-Wlogical-op -Wstrict-null-sentinel
LDFLAGS+=
else
CXXFLAGS+=
LDFLAGS+=
endif
