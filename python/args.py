#!/usr/bin/python3

import argparse

parser = argparse.ArgumentParser(description="testing out argparse")
parser.add_argument('-f', help='the file 🐸')
args = parser.parse_args()

print(args.file)
print(ls(parser))
