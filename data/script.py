from random import sample

"""
 Creates a data file of random numbers for inserting and removing numbers
 for 2021 DSU CSC310 Advanced Data Structures AVL Tree.

 Created by Dan Bauer (2021)
"""

# File Values.
N_SIZE = 1000
MIN = 1
MAX = 9999
FILE_NAME = "del2.dat"
N_TO_DELETE = 800

# Creates random samples.
list = sample(range(MIN, MAX), N_SIZE)
list2 = sample(list, N_TO_DELETE)

# Generates the data file.
file = open(FILE_NAME, 'w')
for i in list:
    file.writelines("0\n")
    file.writelines(str(i) + "\n")

file.write("2\n")
for i in list2:
    file.writelines("1\n")
    file.writelines(str(i) + "\n")

file.write("2\n")
file.write("8\n")
file.write("9\n")
file.close()
