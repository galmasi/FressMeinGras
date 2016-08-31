import os
import sys
import matplotlib as plt

def read_coords (fname):
    fd = open(fname, 'rd')
    count=0
    timeline=[]
    result={}
    for line in fd:
        try:
            values = line.split(',')
            if 'GPGGA' in values[0] and values[6] > 0:
                timesig=values[1]
                lat=values[2]
                long=values[4]
                timeline.append(timesig)
                result[timesig]=(lat,long)
        except Exception, e:
            print 'ERROR: %s'%(str(e))
            exit(1)
    return timeline,result

base='/Users/galmasi/SparkleShare/FressMeinGras/GPS/collected_datafiles/083016/'

tl1,ga1 = read_coords ('20160830161544_ga1.txt')
tl2,ga2 = read_coords ('20160830231412_ga2.txt')
tl3,hf1 = read_coords ('20160830161420_hf.txt')
tl4,usb = read_coords ('usbkey.txt')

ga2err=[]
hf1err=[]
usberr=[]

for 
