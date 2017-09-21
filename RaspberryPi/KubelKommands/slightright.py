#!/usr/bin/env python

import serial
import time
import numpy as np
import cv2
import sys

# open serial port for issuing motor commands

ser = serial.Serial(
    port='/dev/ttyUSB0',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_TWO,
    bytesize=serial.EIGHTBITS)

ser.isOpen()

# start video capture device

ser.write("G\n")
ser.write('L-25\n')
ser.write('R25\n')
time.sleep(0.8)
ser.write('L0\n')
ser.write('R0\n')
ser.write("S\n")
