#!/bin/python3

def chop(t):
    t.pop(0)
    t.pop(-1)

def middle(t):
    return t[1:-1]

t = [1, 2, 3, 4]

print(middle(t))
