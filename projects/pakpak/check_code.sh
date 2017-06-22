#!/bin/bash

#
# Static analysis of the project
# Dependencies:
# - cppcheck

cppcheck -I./include/ 				\
	 -I../../libs/logger/include		\
 	 -I../../libs/serializer/include	\
	 -I../../libs/exceptions/include 	\
 	 -I../../libs/crypto/include		\
 	 -I../../libs/multithread/include	\
 	 -I../../libs/network/include		\
	 -I../../libs/packet/include		\
 	 -I../../libs/ini/include		\
	 --enable=all --force --language=c++ --std=c++11 -q --suppress=missingIncludeSystem \
	 --inline-suppr				\
	 --error-exitcode=1 .
exit $?
