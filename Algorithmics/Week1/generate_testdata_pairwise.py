#!/usr/bin/env python3
import random

n = int(input())
min = int(input())
max = int(input())
vals = []

for i in range(0,n):
    val = random.randint(min,max)
    vals.append(val)

print(n)
for i in range(0,n):
    print(vals[i], end=" ")