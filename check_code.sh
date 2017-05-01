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

check_dir "libs/crypto/"
check_dir "libs/logger/"
check_dir "libs/memory/"
exit 0
