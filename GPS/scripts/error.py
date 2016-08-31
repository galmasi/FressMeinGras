import matplotlib as plt

def read_coords (fname):
    fd = open(fname, 'rd')
    count=0
    for line in fd:
        try:
            values = line.split(' ')

