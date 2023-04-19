#!/usr/bin/python3

# print longest line

import sys

lines = []
with open(sys.argv[1], 'r') as f:
    for l in f:
        if l.strip() == '': continue
        lines.append((len(l), l))

for i in sorted(lines):
    print(i[0], i[1], end='')
