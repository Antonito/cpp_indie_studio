#!/bin/bash

#
# Static analysis of the project
# Dependencies:
# - cppcheck

cppcheck -I./include/ -I../../../libs/network/include -I../../../libs/logger/include \
	 -I../../../libs/exceptions/include \
	 -I../../../libs/packet/include \
	 -I../../../libs/crypto/include \
	 -I../../../libs/ini/include \
	 -I../../../libs/serializer/include \
	 --enable=all --force --language=c++ --std=c++11 -q --suppress=missingIncludeSystem \
	 --error-exitcode=1 .
exit $?
