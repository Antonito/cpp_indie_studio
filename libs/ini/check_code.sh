#!/bin/bash

#
# Static analysis of the project
# Dependencies:
# - cppcheck

cppcheck -I./include/ -I../exceptions/include/ \
	 --enable=all --force --language=c++ --std=c++11 \
	 -q --suppress=missingIncludeSystem \
	 --error-exitcode=1 .
exit $?
