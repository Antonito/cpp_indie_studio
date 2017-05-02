#!/usr/bin/env python3

"""
This script generates manages licences.
It allows someone to add licences, or list all the current licences.
"""
import logging
import random

LICENCE_FILE = "./.licence_keys"


def generate_licence():
    KEY = '0123456789ABCDEF'

    key = ''
    for j in range(1, 5):
        for i in range(0, 8):
            key += str(KEY[random.randint(1, len(KEY) - 1)])
        if j != 4:
            key += '-'
    return (key)


def find_licence(key):
    # Check if a licence key is in the licence file
    try:
        rc = open(LICENCE_FILE, 'r').read().find(key)
    except Exception as e:
        return False
    return rc != -1


def add_licence():
    # Add a licence key to the licence file
    key = generate_licence()

    # Loops until the licence is new
    while find_licence(key):
        key = generate_licence()

    print(key)
    with open(LICENCE_FILE, 'a') as f:
        f.write(key + '\n')


def list_licence():
    try:
        with open(LICENCE_FILE, 'r') as f:
            print(f.read(), end='')
    except Exception as e:
        print (e)


# Script starts here
logging.basicConfig(format='%(asctime)s %(message)s',
                    datefmt='%m/%d/%Y %I:%M:%S %p', level=logging.INFO)

logging.info('Starting licence manager.')
logging.info('Writing to file ' + LICENCE_FILE)
# Licence manager loop
while True:
    print('> ', end='')

    # Get input
    msg = input()
    logging.debug('User typed: ' + msg)

    # Process input
    if msg == 'exit':
        break
    elif msg == 'help':
        print('Available commands: exit / help / list / add')
    elif msg == 'list':
        list_licence()
    elif msg == 'add':
        add_licence()
    else:
        print('Invalid command')

logging.info('Stopping licence manager.')
