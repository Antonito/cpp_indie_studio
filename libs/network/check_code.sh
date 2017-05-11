#!/bin/bash

#
# Static analysis of the project
# Dependencies:
# - cppcheck

cppcheck -I./include/ -I../exceptions/include/ -I../logger/include/ \
	 -I../packet/include \
	 --enable=all --force --language=c++ --std=c++11 -q --suppress=missingIncludeSystem \
	 --inline-suppr \
	 --error-exitcode=1 .
exit $?
