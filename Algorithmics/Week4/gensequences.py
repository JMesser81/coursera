import sys
import subprocess
from random import randint

def main(argv):
    numitems = int(argv[1])
    print("Creating random input with ", numitems, " elements!")
    input = str(numitems) + "\n"
    for i in range(numitems):
        input += str(randint(0,5)) + " "

    print("Sending ", input)
    
    # call qsort-3waysplit
    cmd = "./qsort-3waysplit"
    p = subprocess.run(cmd, stdout=subprocess.PIPE, input=input.encode('ascii'))
    output = p.stdout.decode()
    print(output)

if __name__ == "__main__":
    main(sys.argv)
