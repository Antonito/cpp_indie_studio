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

def susePack():
    print("OpenSUSE")
    print("To code of course")

def archPack():
    print("ArchLinux")
    print("To code of course")

def debianPack():
    print("debian")
    print("To code of course")

def ubuntuPack():
    print("debian")
    print("To code of course")

def fedoraPack():
    print("fedora")
    print("To code of course")

def gentooPack():
    print("fedora")
    print("To code of course")

def checkLinux():
    distribMap = {"arch" : archPack, "Ubuntu" : ubuntuPack, "OpenSUSE" : susePack, "debian" : debianPack, "fedora" : fedoraPack, "gentoo" : gentooPack}
    distribName = platform.linux_distribution()[0]
    try:
        distribMap[distribName]()
    except:
        print("Your Linux distribution is not officialy supported :'(")

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
        print("For Linux installation please check the installation script !")
        #checkLinux()
    else:
        print("Error, cannot identify the target :/")
        sys.exit(1)

sys.exit(0)
