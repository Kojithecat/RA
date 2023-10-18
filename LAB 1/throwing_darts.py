import random as rand
import math
import matplotlib.pyplot as plt

#Throw N darts and return the approximeted value of pi
def throw_darts_independent(N):
    for i in range(N):
        dart_x = rand.uniform(0,1)
        dart_y = rand.uniform(0,1)
        if (dart_x - 0.5)**2 + (dart_y - 0.5)**2 < 0.25:
            C += 1
    return 4*C/N

#Throw N darts and return the approximeted value of pi, the one used for the experiment
#Cant and Nant are parameters to allow a progressive approximation of pi e.g(N: 1000, 10000, 100000) 
def throw_Ndarts(N,Cant = 0,Nant = 0):
    C = 0
    N = N-Nant
    for i in range(N):
        dart_x = rand.uniform(0,1)
        dart_y = rand.uniform(0,1)
        if (dart_x - 0.5)**2 + (dart_y - 0.5)**2 < 0.25:
            C += 1
    print(N+Nant)
    return 4*(C+Cant)/(N+Nant), C+Cant, N+Nant

def main():
    #Tests
    C = 0
    N = 0
    l = []
    it = []
    error = []
    for i in range(2,10): #from 100 to 1.000.000.000 needles
        r,C,N = throw_Ndarts(10**i,C,N)
        l.append(r)
        it.append(10**i)
        print(abs((math.pi - r)/math.pi))
        error.append(abs((math.pi - r)/math.pi))
        print(r)

    fig, ax = plt.subplots() #Graph for the pi approximation
    ax.plot(it,l)
    ax.set_xscale("log")
    ax.set(xlabel="Nº iterations", ylabel="Approximated pi value", title= "Pi approximation with throwing darts approach")
    ax.grid()
    plt.axhline(y=math.pi, color='r', linestyle='-',linewidth = 0.5)
    plt.show()

    fig, ax = plt.subplots() #Graph for the relative error
    ax.plot(it,error)
    ax.set_xscale("log")
    ax.set(xlabel="Nº iterations", ylabel="Error", title= "Relative error of the approximation of pi")
    ax.grid()
    plt.show()


if __name__ == "__main__":
    main()
