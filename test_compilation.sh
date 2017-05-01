#!/bin/sh

##
## This script tries every possible way to compile the project.
##

echo "Debug Compilation"
make re CXX=g++ DEBUG=yes
make re CXX=clang++ DEBUG=yes
make re TARGET=WIN32 DEBUG=yes
make re TARGET=WIN64 DEBUG=yes

echo "Release Compilation"
make re CXX=g++ DEBUG=no
make re CXX=clang++ DEBUG=no
make re TARGET=WIN32 DEBUG=no
make re TARGET=WIN64 DEBUG=no

echo "Done."
