import csv
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np
import math

# opening the CSV file
with open('plots/comparisonsExtraQS.txt', mode ='r')as file:

    # reading the CSV file
    csvFile = csv.reader(file)

    delta = 2000
    n = 40000
    l = []

    # displaying the contents of the CSV file
    for lines in csvFile:
        l.append(list(map(lambda x: x/n ,map(int, lines))))

    labs = [delta*j/n for j in range(len(l))]
    labs[0] = 0.000001

    theo = [2 - 2*(a*math.log(a) + (1 - a)*math.log(1 - a)) for a in labs]
    labs[0] = 0


    plt.boxplot(l, vert=True, patch_artist=True, labels=labs)
    plt.plot(range(1,len(l)+1),theo,color = "red", linestyle = "-",linewidth = 2)


    plt.xlabel("alpha",fontsize = 15)
    plt.ylabel("Average num of comparisons divided by n",fontsize = 15)

    plt.xticks(fontsize = 15)
    plt.yticks(fontsize = 15)

    plt.show()
