#!/usr/bin/env python3

import argparse
import os

import pylibftdi

parser = argparse.ArgumentParser()
args = parser.parse_args()

with pylibftdi.bitbang.BitBangDevice(interface_select=0) as bb:
    bb.direction = 0b1000 # ADBUS3
    bb.port = 0b1000
    print("DEBUG_RTS is now high.... reset to enter recovery. Interrupt/hit enter to release DEBUG_RTS")
    try:
        input()
    except KeyboardInterrupt:
        pass

    bb.port = 0x0
    bb.direction = 0x0
