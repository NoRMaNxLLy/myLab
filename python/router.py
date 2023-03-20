#!/bin/python3

from telnetlib import Telnet

with Telnet('localhost') as R:
    recv = R.read_eager();
    print(recv)
