#!/bin/python3

import sys
import re

if len(sys.argv) < 2:
    print('%s PATTERN FILE' % sys.argv[0])
    exit(1)

pattern, fname = sys.argv[1:]

with open(fname, 'r') as file:
    for line in file:
        if re.search(pattern, line):
            print(line.rstrip())

