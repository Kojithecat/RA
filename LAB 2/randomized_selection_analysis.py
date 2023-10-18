import csv
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np
import math

# opening the CSV file
with open('plots/comparisonsAlg2.txt', mode ='r')as file:

    # reading the CSV file
    csvFile = csv.reader(file)

    delta = 10000
    nmax =  200000
    nperm = 1000
    ns = [x for x in range(delta,nmax,delta)]
    print(ns)
    l = []
    l2 = []

    # displaying the contents of the CSV file
    i = delta
    for lines in csvFile:
        l.append(list(map(lambda x: x/i ,map(int, lines))))
        i += delta
        l2.append(list(map(int, lines)))

    print(i)
    print(len(ns))
    print(len(l))

    plt.boxplot(l, vert=True, patch_artist=True, labels=ns)

    #plt.boxplot(l2, vert=True, patch_artist=True, labels=ns)

    #plt.show()

    plt.xlabel("n",fontsize = 13)
    plt.ylabel("Num of comparisons",fontsize = 13)



    plt.xticks(fontsize = 13)
    plt.yticks(fontsize = 13)


    plt.show()
