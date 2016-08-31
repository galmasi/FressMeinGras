import os
import sys
import matplotlib as plt

def read_coords (fname):
    fd = open(fname, 'rd')
    count=0
    result=[]
    for line in fd:
        try:
            values = line.split(',')
            if 'GPGGA' in values[0] and values[6] > 0:
                timesig=values[1]
                lat=values[2]
                long=values[4]
                result.append((timesig,lat,long))
        except Exception, e:
            print 'ERROR: %s'%(str(e))
            exit(1)

base='/Users/galmasi/SparkleShare/FressMeinGras/GPS/collected_datafiles/083016/'

20160830161420_hf.txt20160830161544_ga1.txt20160830231412_ga2.txtusbkey.txt



ga1 = read_coords ('20160830161544_ga1.txt')
ga2 = read_coords ('20160830231412_ga2.txt')
hf1 = read_coords ('20160830161420_hf.txt')
