#!/bin/sh

#
# This script starts the licenseManager and the connectManager
#

BUILD_FOLDER="./build/"
LICENSE_MANAGER=license_manager.py
CONNECT_MANAGER=./connect_manager

echo "TODO: Script is not finised \!"
cd "$BUILD_FOLDER";

./"$LICENSE_MANAGER" &
#./"$CONNECT_MANAGER" 1123 12345 12346
fg
