import os
import sys
import time
import androidhelper

counter=1

droid = androidhelper.Android()
droid.startLocating()


time.sleep(15)

while True:
    loc = droid.readLocation().result
    if loc == {}:
        loc = droid.getLastKnownLocation().result
    if loc != {}:
        try:
            n = loc['gps']
        except KeyError:
            n = loc['network']

    la = n['latitude'] 
    lo = n['longitude']
    address = droid.geocode(la, lo).result

    print '----------------------------'
    print counter
    print la,lo
    print address
    print

    time.sleep(10)
    counter+=1
    
