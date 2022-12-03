import random
import numpy
import time
from array import array
import sumarr

mylist = numpy.arange(0, 100000, 1).tolist()
#mylist= [random.randint(1,100) for i in range (0,100)]
# with numpy
start_time = time.time()
sum1 = numpy.sum(mylist)
print("numpy")
print("--- %s seconds ---" % (time.time() - start_time))

#function sum
start_time = time.time()
sum2 = sum(mylist)
print("function sum")
print("--- %s seconds ---" % (time.time() - start_time))

#normal
print("normal")
start_time = time.time()
sum3 =0
for i in range(0, len(mylist)):
    sum3 +=mylist[i]

print("--- %s seconds ---" % (time.time() - start_time))



start_time = time.time()

print("cpp")
sumarr.add(mylist)

print("--- %s seconds ---" % (time.time() - start_time))

