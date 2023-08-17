#!/usr/bin/python3

# prime test

def is_prime(n):
    for d in range(2, n):
        if (d * d > n): break
        if (n % d == 0): return False

    return True

for i in range(2,100):
    if is_prime(i):
        print(i)
