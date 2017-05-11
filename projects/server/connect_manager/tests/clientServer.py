#!/usr/bin/env python3
# coding: utf-8

#TODO: RE-DO the whole protocol communication : eg "Hello connectManager" -> breuh
"""

This script emulates the gameServer behavior.

Packet:

    uint16_t magicNumber (2)
    uint16_t size (packet size)
    uint16_t checksum (checksum of the packet)
    char data[]

Protocol:
GS == gameServer (this script)
CM == ConnectManager

## Unknwon
GS ==> "HELLO" ==> CM

CM ==> "WHO ?" ==> GS

## Connecting
GS ==> "LICENCEPORT" ==> CM // . means char[] .. means uint16_t .... means uint32_t

CM ==> "OK" ==> GS

## Valid

GS is connected as a server


"""

import socket
import time
import logging
import threading
import argparse
import sys
import ctypes
from collections import namedtuple
from time import sleep

__author__ = "Antoine Baché"

gameServerPortL = (12345)
gameServerMaxClientL = (4096)
gameServerPort = gameServerPortL.to_bytes(2, byteorder='big')
gameServerMaxClient = gameServerMaxClientL.to_bytes(4, byteorder='big')

def gamServerTestEndMsg(logger, name, ite, err):
    logger.info("[OK] Succes: %.2f%% Fail: %d Total: %d | Name: %s" % \
                (((ite - err) / ite) * 100.0, err, ite, name))


def createHeader(data):
    
    summ = 0
    magick = 0x1D00
    size = len(data)
    for i in range(len(data)):
        summ += int(bytes(str(data[i]), 'utf-8'))
    summ &= 0xFFFF
    header = magick.to_bytes(2, byteorder='big') + size.to_bytes(2, byteorder='big') + summ.to_bytes(2, byteorder='big')
    return (header)

def connectProtocol(logger, sock):

    print("OMGOMGOMGOMGGOGMOGMGOMOGMOGMMGO")

    licence = ""
    try:
        with open(".licence", "r") as licenceFile:
            licence = licenceFile.read().strip()
    except (OSError, IOError) as e:
        print(e)
        print("Will exit now")
        sys.exit()

    MyStruct = namedtuple("Packet", "field1 field2 field3 field4")

    #msg = b"HELLO"
    eventType = 0
    data = eventType.to_bytes(2, byteorder='big')
    header = createHeader(data)
    pck = header + data
    sock.send(pck);

    msg = sock.recv(4096); # "Hello, who are you ?"
    print("SEND HELLO")

    if (msg != b"WHO ?"):
        #sock.close()
        #logger.debug("Wrong server answer. Received: \"%s\"" % (msg))
        #return (1);
        for i in range(len(msg)):
            try:
                print(str(msg[i]).decode)
            except:
                continue
        print("Of course")

    msg = bytes(licence, 'utf-8')
    for i in range(256 - len(msg)):
        msg += b"\x00"
    msg += (8080).to_bytes(2, byteorder='big')
    eventType = 0
    data = eventType.to_bytes(2, byteorder='big') + msg
    header = createHeader(data)
    pck = header + data
    sock.send(pck);

    msg = sock.recv(4096); # "OK"
    if (msg != b"OK, welcome gentleman."):
        #sock.close()
        #logger.debug("Wrong server answer. Received: \"%s\"" % (msg))
        #return (1);
        print("Of course")

    logger.debug("GameServer is connected\n");
    return (0);

def gameServerBruteForce(logger, host, port, ite):

    logger.info("Starting BruteForce [Ite: %d]" % (ite))

    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    except Exception as e:
        logger.critical(e)
        return
    try:
        sock.connect((host, port))
    except Exception as e:
        logger.critical(e)
        return


    err = 0;
    logger.info("Connected on {}:{}".format(host, port))

    step = ite / 20

    i = 0
    while (i < ite):
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        except Exception as e:
            logger.critical(e)
            return
        try:
            sock.connect((host, port))
        except Exception as e:
            logger.critical(e)
            return

        if ((i % step) == 0):
            logger.debug("Loop %d" % (i))
        err = err + connectProtocol(logger, sock)
        sock.close()
        i = i + 1

    gamServerTestEndMsg(logger, "BruteForce", ite, err)

def gameServerSlow(logger, host, port, ite, delay):

    logger.info("Starting Slow Test [Ite: %d | Delay: %.4fsecs]" % (ite, delay))

    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except Exception as e:
        logger.critical(e)
        return
    try:
        sock.connect((host, port))
    except Exception as e:
        logger.critical(e)
        return

    err = 0
    logger.info("Connected on {}:{}".format(host, port))

    step = ite / 20

    i = 0
    while (i < ite):
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        except Exception as e:
            logger.critical(e)
            return
        try:
            sock.connect((host, port))
        except Exception as e:
            logger.critical(e)
            return

        if ((i % step) == 0):
            logger.debug("Loop %d" % (i))
        err = err + connectProtocol(logger, sock)
        sock.close()
        time.sleep(delay);
        i = i + 1

    gamServerTestEndMsg(logger, "Slow", ite, err)

def gameServerTestSlowMt(logger, host, port, ite, delay, nbThreads):
    threads = [None] * nbThreads

    # Test thread Slow
    logger.info("Starting Multithread test[%d]: Slow" % (nbThreads));
    for i, obj in enumerate(threads):
        threads[i] = threading.Thread(target=gameServerSlow, \
                                      args=(logger, host, port, ite, delay))
    for i in threads:
        i.start()

    for i in threads:
        i.join()

def gameServerBenchmarkMT(logger, host, port, ite, nbThreads):
    threads = [None] * nbThreads

    logger.info("Starting Multithread test[%d]: Bruteforce" % (nbThreads));
    for i, obj in enumerate(threads):
        threads[i] = threading.Thread(target=gameServerBruteForce, \
                                      args=(logger, host, port, ite))
    for i in threads:
        i.start()

    for i in threads:
        i.join()

def gameServer(logger, host, port):
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except Exception as e:
        logger.critical(e)
        return
    try:
        sock.connect((host, port))
    except Exception as e:
        logger.critical(e)
        return

    connectProtocol(logger, sock)
    # Loops until you type "exit"
    while (1):
        print("> ", end="")
        msg = input()
        if (msg == "exit"):
            break
        if (msg != ""):
            sock.send(msg.encode())
            print(sock.recv(256).decode())

    return

def single_thread_tests(logger, addr, port):
    # Single-Threaded
    logger.info("Starting single-threaded tests")
    try:
        gameServerSlow(logger, addr, port, 1000, 0.02)
    except Exception as e:
        logger.critical("gameServerTestSlow #1:" + str(e))
    try:
        gameServerBruteForce(logger, addr, port, 10000)
    except Exception as e:
        logger.critical("gameServerBruteForce #2:" + str(e))
    try:
        gameServerBruteForce(logger, addr, port, 100000)
    except Exception as e:
        logger.critical("gameServerBruteForce #3:" + str(e))
    logger.info("Finished single-threaded tests")

def multithread_tests(logger, addr, port):
    # Multithreaded
    logger.info("Starting multithreaded tests")
    try:
        gameServerTestSlowMt(logger, addr, port, 1000, 0.02, 25)
    except Exception as e:
        logger.critical("gameServerTestSlowMt #1:" + str(e))
    try:
        gameServerBenchmarkMT(logger, addr, port, 1000, 25)
    except Exception as e:
        logger.critical("gameServerBenchmarkMt #2:" + str(e))
    try:
        gameServerTestSlowMt(logger, addr, port, 200, 0.02, 1000)
    except Exception as e:
        logger.critical("gameServerTestSlowMt #3:" + str(e))
    try:
        gameServerTestSlowMt(logger, addr, port, 100, 0.2, 200)
    except Exception as e:
        logger.critical("gameServerTestSlowMt #4:" + str(e))
    try:
        gameServerBenchmarkMT(logger, addr, port, 100, 200)
    except Exception as e:
        logger.critical("gameServerBenchmarkMt #5:" + str(e))
    try:
        gameServerBenchmarkMT(logger, addr, port, 100, 800)
    except Exception as e:
        logger.critical("gameServerBenchmarkMt #6:" + str(e))
    try:
        gameServerBenchmarkMT(logger, addr, port, 100, 1000)
    except Exception as e:
        logger.critical("gameServerBenchmarkMt #7:" + str(e))
    try:
        gameServerBenchmarkMT(logger, addr, port, 100, 1200)
    except Exception as e:
        logger.critical("gameServerBenchmarkMt #8:" + str(e))
    logger.info("Finished multithreaded tests")

def full_test(logger, addr, port):
    logger.info("Starting full tests")
    single_thread_tests(logger, addr, port)
    multithread_tests(logger, addr, port)
    logger.info("Finished full tests")

if __name__ == "__main__":

    # Parse arguments
    parser = argparse.ArgumentParser(description="Test your connectManager")
    parser.add_argument("--mode", action="store", dest="mode", required=True, \
                        help="Mode: full / single-threaded / multithreaded / shell / single")
    res = parser.parse_args()

    # Create logger
    logger = logging.getLogger()
    logger.setLevel(logging.DEBUG)
    formatter = logging.Formatter('%(asctime)s :: %(levelname)-8s :: %(message)s')

    # Create Handler
    fileHandler = logging.FileHandler("../logs/gameserver_py.log", "w")
    fileHandler.setLevel(logging.DEBUG)
    fileHandler.setFormatter(formatter)

    streamHandler = logging.StreamHandler()
    streamHandler.setLevel(logging.INFO)
    streamHandler.setFormatter(formatter)

    # Add handlers to logger
    logger.addHandler(streamHandler)
    logger.addHandler(fileHandler)

    # Start tests
    logger.info("GameServer | Port: %d | MaxClient: %d" % (gameServerPortL, gameServerMaxClientL))

    if (res.mode == "full"):
        full_test(logger, "localhost", gameServerPortL)
    elif (res.mode == "single-threaded"):
        single_thread_tests(logger, "localhost", gameServerPortL)
    elif (res.mode == "multithreaded"):
        multithread_tests(logger, "localhost", gameServerPortL)
    elif (res.mode == "shell"):
        gameServer(logger, "localhost", gameServerPortL)
    elif (res.mode == "single"):
        gameServerTestSlowMt(logger, "localhost", gameServerPortL, 1000, 0.2, 1000)

    exit(0)
