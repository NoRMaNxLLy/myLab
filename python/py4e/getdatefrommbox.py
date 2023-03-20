#!/bin/python3

count = 0
with open('mbox-short.txt') as fhand:
    for line in fhand:
        if not line.startswith('From'): continue
        words = line.split()
        if len(words) < 3: continue
        print(words[2])
