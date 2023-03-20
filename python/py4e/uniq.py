#!/bin/python3

words = {}

with open('romeo.txt', 'r') as txt:
    for line in txt:
        for w in line.split():
            words[w] = words.get(w, 0) + 1

words_unsorted = []
for k, v in words.items():
    words_unsorted.append((v, k))

words_unsorted.sort()

for k, v in words_unsorted:
    print(k, v)
