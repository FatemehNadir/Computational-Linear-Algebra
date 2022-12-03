import cppimport
import numpy as np
import random
import time

code = cppimport.imp("wrap4")

if __name__ == '__main__':
   
  
    mylist = random.sample(range(100000), 100000)
    #print (mylist)
   
    # simple 
    ts = time.time()
    su = 0
    for i in range(0, len(mylist)):
    	su += mylist[i]
    #print(su)
    t0 = (time.time() - ts)
    print("1-SIMPLE\t: %s seconds " % t0)


    #function sum in PYTHON
    ts = time.time()
    sum(mylist)
    t1 = (time.time() - ts)
    print("2-PYTHON\t: %s seconds " % t1)

    #function sum in NUMPY
    ts = time.time()
    np.sum(mylist)
    t2 = (time.time() - ts)
    print("3-NUMPY\t\t: %s seconds " % t2)


    #function sum in CPP (normal)
    ts = time.time()
    code.sum(mylist)
    t3 = (time.time() - ts)
    print("4-CPP\t\t: %s seconds " % t3)


    #function sum in CPP - OPENMP (parallel)
    ts = time.time()
    code.summp(mylist)
    t4 = (time.time() - ts)
    print("5-OPENMP\t: %s seconds " % t4)

    print ("**MIN[3-5]\t:",min(t2,t3,t4))



