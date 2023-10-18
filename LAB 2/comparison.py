import csv
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np
import math

# opening the CSV file
with open('plots/comparisonsExtraQS.txt', mode ='r')as file:

    # reading the CSV file
    QSFile = csv.reader(file)

    with open('plots/comparisonsExtraRS.txt', mode ='r')as file:

        RSFile = csv.reader(file)

        with open('plots/comparisonsMedian3.txt', mode ='r')as file:

            QS3File = csv.reader(file)

            delta = 10000
            nmax =  200000
            nperm = 1000

            lQS = []
            lRS = []
            lQS3 = []
            for lines in QSFile:
                s = 0
                lQS.append(sum(map(int, lines))/len(lines))

            for lines in RSFile:
                lRS.append(sum(map(int, lines))/len(lines))

            for lines in QS3File:
                lQS3.append(sum(map(int, lines))/len(lines))

            print(lQS)
            print(lRS)

            labs = [x for x in range(10000, nmax, delta)]

            plt.plot(labs, lQS, color = "r")
            plt.plot(labs, lRS, color = "g")
            plt.plot(labs, lQS3, color = "b")

            plt.legend(["Quickselect","Randomized selection", "Quickselect with median of 3"],fontsize = 15)

            plt.ylabel("Average num of comparisons",fontsize = 20)

            plt.xticks(fontsize = 15)
            plt.yticks(fontsize = 15)

            plt.show()
