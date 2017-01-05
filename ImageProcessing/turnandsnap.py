#!/usr/bin/env python

# ######################################################
# snap 30 pictures while turning the rover in a circle
# ######################################################


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
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS)

ser.isOpen()

# start video capture device

vc1 = cv2.VideoCapture(0)

print "Picture dimensions: %d x %d"%(vc1.get(3),vc1.get(4))


# start snapping pictures and turning right

npics=30

for counter in xrange(1,npics):

    print "Snapping picture %d/%d"%(counter,npics)
    ret1, frame1 = vc1.read()
    picfile="picture%d.jpg"%(counter)
    cv2.imwrite(picfile, frame1);
    counter+=1

    print "Panning right"
    ser.write('L-5\n')
    ser.write('R5\n')
    time.sleep(0.2)
    ser.write('L-20\n')
    ser.write('R20\n')
    time.sleep(0.4)
    ser.write('L-5\n')
    ser.write('R5\n')
    time.sleep(0.2)
    ser.write('L0\n')
    ser.write('R0\n')

    print "Waiting 2s for stability"
    time.sleep(2)
    
