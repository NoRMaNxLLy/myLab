#!/bin/python3

import urllib.request as request

img_url = request.urlopen('http://data.pr4e.org/cover3.jpg')
img_file = open('cover3.jpg', 'wb')

size = 0
while True:
    buffer = img_url.read(1024)
    if len(buffer) < 1: break
    size += len(buffer)
    img_file.write(buffer)

img_url.close()
img_file.close()

print(size / 10 ** 6)
