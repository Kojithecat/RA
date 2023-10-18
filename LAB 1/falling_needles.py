from random import uniform
import math
import matplotlib.pyplot as plt

#Throw N needles and return the approximeted value of pi
#Cant and Nant are parameters to allow a progressive approximation of pi e.g(N: 1000, 10000, 100000) 
def throw_Nsticks(N,Cant=0,Nant=0): 
    C = 0
    l = 0.5
    T = 1
    N = N-Nant
    for i in range(N):
        stick_x = uniform(0,0.5)
        stick_angel = uniform(0,math.pi/2)
        if (stick_x <= l*0.5 * math.sin(stick_angel)):
            C += 1
    N = N+Nant
    C = C+Cant
    return 2*l*N/(T*C),C,N

def main():
    C = 0
    N = 0
    l = []
    it = []
    error = []
    for i in range(2,10): #from 100 to 1.000.000.000 needles
        r,C,N = throw_Nsticks((10**i),C,N)
        l.append(r)
        it.append(10**i)
        print(abs((math.pi - r)/math.pi))
        error.append(abs((math.pi - r)/math.pi))
        print(r)
    
    fig, ax = plt.subplots() #Graph for the pi approximation
    ax.plot(it,l)
    ax.set_xscale("log")
    ax.set(xlabel="Nº iterations", ylabel="Approximated pi value", title= "Pi approximation with falling needles approach")
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
