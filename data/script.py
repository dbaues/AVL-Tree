from random import randint
from random import sample

N_SIZE = 50
MIN = 1
MAX = 500
FILE_NAME = "tmp9.dat"

list = []
list2 = []
""" #DEPRECATED
while len(list) < N_SIZE:
    x = randint(MIN, MAX)
    if x not in list:
        list.append(x)
"""
list = sample(range(MIN,MAX),N_SIZE)
list2 = sample(list, int(N_SIZE/2))

file = open(FILE_NAME, 'w')
for i in list:
    file.writelines("0\n")
    file.writelines(str(i) + "\n")

file.write("2\n")
for i in list2:
    file.writelines("1\n")
    file.writelines(str(i) + "\n")

file.write("2\n")
file.write("9\n")
file.close()
