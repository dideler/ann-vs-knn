#!/usr/bin/env python
"""
Takes all the values in a file and averages them.
File name can be provided as the first program argument, or user input.
"""
from sys import argv
try:
    if len(argv) > 1:
        filename = argv[1]
    else:
        filename = input('Enter file name: ')
    f = open(filename, 'r')
    total = 0
    for counter, num in enumerate(f):
        total += float(num)
    print 'Average is', total / (counter + 1)
except:
    print 'Oops. File name correct?'
