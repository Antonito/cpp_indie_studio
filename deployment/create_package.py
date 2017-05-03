import platform
from subprocess import Popen, PIPE

def osxPack():

    process = Popen(['platypus', '-P', 'IndieStudio.platypus', 'indiestudio.app'], stdout=PIPE, stderr=PIPE)
    stdout, stderr = process.communicate()
    rc = process.returncode

    if (rc):
        print stderr
        print "Download here, or error"
    else:
        print "app package ok and ready"
