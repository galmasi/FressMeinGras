import os
import matplotlib as plt

def read_coords (fname):
    fd = open(fname, 'rd')
    count=0
    for line in fd:
        try:
            values = line.split(',')
        except Exception, e:
            print 'ERROR: %s'%(str(e))
            exit(1)

