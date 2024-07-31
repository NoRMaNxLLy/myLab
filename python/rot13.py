#!/usr/bin/python3

from sys import stdin

def rot13(line):
    pass


while True:
    line = stdin.readline().rstrip()
    if len(line) < 1: break
    rot13(line.encode('ascii'))
