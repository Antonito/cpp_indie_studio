#!/usr/bin/env python3

#TODO: change binary Name for package creation

#This script generates package for each available platform (Windows, OS X, Linux)
#It manages all dependencies aswell
#
#
# OS X:
#      MANDATORY:
#       brew install platypus (command line tool used by this script)
#      OPTIONAL:
#       platypus GUI : https://github.com/sveinbjornt/Platypus



import platform
import sys
from subprocess import Popen, PIPE

version = "0.1-1"

def osxPack():

    process = Popen(['platypus', '-P', 'IndieStudio.platypus', 'indiestudio.app'], stdout=PIPE, stderr=PIPE)
    stdout, stderr = process.communicate()
    rc = process.returncode

    if (rc):
        print(stderr)
        print("\nERROR, stay calm and check:\n1)Did you 'make' the project ?\n2)Do you have platypus commandline-tool installed ?\n3)The package is already here so delete it and retry\n")
    else:
        print("OS X app package ok and ready")

def windowsPack():
    print("To code of course")

if (__name__ == "__main__"):
    print("Packager version:" + version)
    print("checking target for package creation...\n")
    
    osName = platform.system()

    if (osName == "Darwin"):
        print("Creating indiestudio.app")
        osxPack()
    elif (osName == "Windows"):
        print("Creating indiestudio_installer.exe")
        windowsPack()
    elif (osName == "Linux"):
        print("Creating IDontFuckingKnowWhatIAmDoing")
        checkLinux()
    else:
        print("Error, cannot identify the target :/")
        sys.exit(1)

sys.exit(0)
