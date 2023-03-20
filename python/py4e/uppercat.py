#!/bin/python3

filename = input("enter a file name: ")

with open(filename, 'r') as f:
    for line in f:
        print(line.upper())
