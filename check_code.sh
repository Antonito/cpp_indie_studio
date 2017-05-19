#!/bin/bash

# Static analysis of all source code
# Dependencies:
# - cppcheck

CLEAR="\e[0m"
WHITE="\e[1;97m"
GREEN="\e[1;92m"
RED="\e[1;91m"

function check_dir {
    printf "$WHITE""Checking %s:$CLEAR\n" "$1"

    cd "$1";
    printf "\e[1;93m";
    ./check_code.sh;

    if [[ $? -eq 0 ]]
    then
	printf "$GREEN""--> OK"
    else
	printf "$RED""--> KO"
    fi
    printf "$CLEAR\n"
    cd - &> /dev/null;
}

# Add your directories here

check_dir "libs/crypto/"
check_dir "libs/logger/"
check_dir "libs/memory/"
check_dir "libs/exceptions/"
check_dir "libs/network/"
check_dir "libs/multithread/"
check_dir "libs/packet/"
check_dir "libs/ini/"
check_dir "libs/pythonpp/"
check_dir "projects/server/connect_manager/"
check_dir "projects/server/game_server/"

exit 0
