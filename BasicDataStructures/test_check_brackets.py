#!/usr/bin/env python3
from os import walk
from subprocess import run
from subprocess import PIPE

testfiles = []
answerfiles = []

testdir = input("Enter a directory: ")
for (dirpath, dirnames, filenames) in walk(testdir):
    for f in filenames:
        if f.endswith(".a"):
            answerfiles.append(f)
        else:
            testfiles.append(f)
    break

for t in testfiles:
    myfile = testdir + "/" + t
    myinput = open(myfile)
    proc = run(["./a.out"], shell=True, stdin=myinput, stdout=PIPE)
    myinput.close()

    output = proc.stdout.rstrip()
    output = output.decode('ascii')

    a = open(myfile + ".a", 'r')
    expected = a.read()
    if (not (str(output) == str(expected))):
        print("Invalid output for ", myfile, "\nOutput: ", str(output), "Expected: ", str(expected))
    a.close()
