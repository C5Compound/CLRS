#-*- coding:utf-8 -*-
from random import *

def tofile():
    k = 0
    for i in range(0, 9):
        ls = list(range(k, 18 + 3 * i + k))
        k += 18 + 3 * i
        #shuffle(ls)
        fp = open(str(i) + '.txt', 'w+')
        for j in ls:
            fp.write(str(j) + ' ')
        fp.close()
tofile()