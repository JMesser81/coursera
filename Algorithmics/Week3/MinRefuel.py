#!/usr/bin/python

def MinRefuel(X, n, L):
    numrefuels = 0
    currentrefuel = 0
    #lastrefuel = numrefuels
    while (currentrefuel <= n):
        #currentrefuel = lastrefuel
        lastrefuel = currentrefuel
        while ( (currentrefuel <= n) and (X[currentrefuel+1] - X[lastrefuel]) <= L ):
            currentrefuel = currentrefuel + 1

        if (currentrefuel == lastrefuel):
            return -1 # not possible to make next gas station

        if (currentrefuel <= n):
            numrefuels = numrefuels + 1

        #lastrefuel = currentrefuel
    return numrefuels

def main():
    X=[0, 125, 300, 350, 450, 540, 600, 760, 880, 1000, 1200]
    L = 200
    refuels = MinRefuel(X, len(X)-2, L)
    print("Minimum refuels required = ", refuels)

if __name__ == "__main__":
    main()
