import csv
import numpy
import math
import matplotlib.pyplot as plt

ns = list(range(2000,20000,1000))
print(ns)
qs = [0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9]

file = open("number_pointers.csv", "r")
data = list(csv.reader(file, delimiter=","))

print(data[0])

#q = 0.5
#theoretical = [n/0.5 + math.log(n,2) for n in ns]
#empirical = [int(x) for x in data[4]]
#print(theoretical)
#print(empirical)

#plt.title('Q = 0.5')

#plt.xlabel('skip list size')
#plt.ylabel('num pointers')

#plt.plot(ns,theoretical,"--")
#plt.plot(ns,empirical,":")

#plt.legend(['Theoretical', 'Empirical'], loc=4)

n = 10000

theoretical = [n/(1-q) + math.log(n,1/q) for q in qs]
empirical = [int(x[8]) for x in data]
print(theoretical)
print(empirical)

plt.title('n = 10000')

plt.xlabel('probability q')
plt.ylabel('num pointers')

plt.plot(qs,theoretical,"--")
plt.plot(qs,empirical,":")

plt.legend(['Theoretical', 'Empirical'], loc=4)


plt.show()
