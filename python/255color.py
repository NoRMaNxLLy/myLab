#!/usr/bin/python3

import os

cols = os.get_terminal_size().columns
numfields = cols / 5

count = 1
for i in range(256):
    if count >= numfields:
        count = 1
        print()
    print(f'\033[48;5;{i}m \033[0m%-4d' % i, end='')
    count += 1
print()
