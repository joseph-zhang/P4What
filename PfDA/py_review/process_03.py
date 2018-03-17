#!usr/bin/env python
#coding=utf-8
# comminication between multiprocessing
import time, random, os
from multiprocessing import Process, Queue

def write_fun(que):
    """ use this function to write something in a queue """
    print('writing process: (%s)'%(os.getpid()))
    for val in ['data_%d'%(i) for i in range(5)]:
        print('put %s to queue.' %(val))
        que.put(val)
        time.sleep(random.random())

def read_fun(que):
    """ use this function to read from a queue """
    print('reading process: (%s)'%(os.getpid()))
    while True:
        val = que.get(True)
        print('Get %s from queue.'%(val))

if __name__ == '__main__':
    que = Queue()
    pw = Process(target = write_fun, args = (que,))
    pr = Process(target = read_fun, args = (que,))
    pr.start()
    pw.start()
    pw.join()
    pr.terminate() # stop pe subprocess
        
