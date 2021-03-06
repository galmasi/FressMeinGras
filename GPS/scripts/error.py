import os
import sys
import matplotlib as plt
import math

def read_coords (fname):
    fd = open(fname, 'rd')
    count=0
    timeline=[]
    result={}
    for line in fd:
        try:
            values = line.split(',')
            if 'GPGGA' in values[0] and values[6] == '1':
                print values
                timesig=values[1]
                lat=float(values[2])
                long=float(values[4])
                timeline.append(timesig)
                result[timesig]=(lat,long)
        except Exception, e:
            print 'ERROR: %s'%(str(e))
            print values[2],values[4]
            exit(1)
    return timeline,result

def nmea2rad (v):
    degrees = int(v/100)
    minutes = v - 100*degrees
    radians = math.PI/180 * (degrees + minutes/60)
    return radians

# ######## processing this now ################

def nmea2meters (lat, lon, lat2, lon2){  // generally used geo measurement function
    var R = 6378.137; // Radius of earth in KM
    var dLat = (lat2 - lat1) * Math.PI / 180;
    var dLon = (lon2 - lon1) * Math.PI / 180;
    var a = Math.sin(dLat/2) * Math.sin(dLat/2) +
    Math.cos(lat1 * Math.PI / 180) * Math.cos(lat2 * Math.PI / 180) *
    Math.sin(dLon/2) * Math.sin(dLon/2);
    var c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
    var d = R * c;
    return d * 1000; // meters
}


def cdiff (c1,c2):
    xd=c1[0]-c2[0]
    yd=c1[1]-c2[1]
    return math.sqrt(xd*xd+yd*yd)



base='/Users/galmasi/SparkleShare/FressMeinGras/GPS/collected_datafiles/083016/'

tl1,ga1 = read_coords (base+'/'+'20160830161544_ga1.txt')
tl2,ga2 = read_coords (base+'/'+'20160830231412_ga2.txt')
tl3,hf1 = read_coords (base+'/'+'20160830161420_hf.txt')
tl4,usb = read_coords (base+'/'+'usbkey.txt')

ga2err=[]
hf1err=[]
usberr=[]

# we use TL1 as the base timeline

for ts in tl1:
    c1 = ga1[ts]

    try:
        c2 = ga2[ts]
        d2 = cdiff(c1,c2)
        print ts, d2
    except:
        pass

    try:
        c3 = ga3[ts]
        d3 = cdiff(c1,c2)
        print ts, d3
    except:
        pass
