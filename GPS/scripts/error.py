import os
import sys
import matplotlib as plt

def read_coords (fname):
    fd = open(fname, 'rd')
    count=0
    for line in fd:
        try:
            values = line.split(',')
            if 'GPGGA' in values[0]:
                print values
        except Exception, e:
            print 'ERROR: %s'%(str(e))
            exit(1)


read_coords ('/Users/galmasi/SparkleShare/FressMeinGras/GPS/collected_datafiles/083016/20160830161544_ga1.txt')
