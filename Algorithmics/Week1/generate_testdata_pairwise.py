#!/usr/bin/env python3
from os import system
import random

n = 1000002 #int(input())
min = 1   #int(input())
max = 2*10**5 # int(input())
vals = []

for i in range(0,n):
    val = random.randint(min,max)
    vals.append(val)


print(n, "\n")
for i in range(0,n):
    print(vals[i], end="\n")