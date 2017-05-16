#!/usr/bin/env python3

'''
This script starts the connectManager server (connectManager binary and licence server)
'''

import os
import subprocess
import threading
from time import sleep

BUILD_FOLDER = r"./build/"

LICENSE_MANAGER = r"./license_manager.py"
LICENSE_DATABASE = r".license_keys"

LICENSE_SERVER_PORT = r"1123"
GAME_SERVER_PORT = r"12346"
GAME_CLIENT_PORT = r"12345"

CONNECT_MANAGER = ["./connect_manager",
                   LICENSE_SERVER_PORT, GAME_SERVER_PORT, GAME_CLIENT_PORT]


def connect_manager_printer(proc):
    while proc.poll() is None:
        line = proc.stdout.readline()
        print("[CONNECT_MANAGER] - " + line.decode(), end='')


# Starts logger
has_licenses = False
if os.path.isfile(BUILD_FOLDER + LICENSE_DATABASE):
    has_licenses = True

# Starts servers
LICENSE_MANAGER_PROC = subprocess.Popen(
    [LICENSE_MANAGER], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, cwd=BUILD_FOLDER)

sleep(0.1)

CONNECT_MANAGER_PROC = subprocess.Popen(
    CONNECT_MANAGER, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, cwd=BUILD_FOLDER)

sleep(0.1)

# Generate license, if needed
print(has_licenses)
if has_licenses is False:
    LICENSE_MANAGER_PROC.stdin.write(b"add")
    LICENSE_MANAGER_PROC.stdin.close()


thread = threading.Thread(
    target=connect_manager_printer, args=(CONNECT_MANAGER_PROC, ))
thread.start()

while LICENSE_MANAGER_PROC.poll() is None:
    line = LICENSE_MANAGER_PROC.stdout.readline()
    print("[LICENSE_SERVER]  - " + line.decode(), end='')

thread.join()
