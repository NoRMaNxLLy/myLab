#!/bin/python3

import socket
import sys
import time

#if len(sys.argv) < 2:
#    url = input('Url: ')
#else:
#    url = sys.argv[1]

url = 'www.gnu.org'
resource = 'http://www.gnu.org/software/gawk/manual/gawk.txt'
cmd = f'GET {resource} HTTP/1.0\r\n\r\n'.encode()

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.connect((url, 80))
    sock.send(cmd)
    while True:
        time.sleep(0.25)
        recv = sock.recv(1024)
        if len(recv) < 1:
            break
        print(recv.decode(), end='')


