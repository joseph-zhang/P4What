#!usr/local/env python
#coding=utf-8
# show how to use basic multiprocessing in python
import time, os, random
from multiprocessing import Process, Pool
import subprocess

def task(name):
    print('Run task %s (%s)...' % (name, os.getpid()))
    start = time.time()
    time.sleep(random.random() * 3)
    end = time.time()
    print('Task %s runs %0.2f seconds.' % (name, (end - start)))
    

def testing1():
    # works only on Unix-like system
    print('Process (%s) start...' % os.getpid())
    pid = os.fork()
    if pid == 0:
        print('I am child process (%s) and my parent is %s.' % (os.getpid(), os.getppid()))
    else:
        print('I (%s) just created a child process (%s).' % (os.getpid(), pid))

def testing2():
    print('Process (%s) is running...' % os.getpid())
    p = Process(target = task, args = ('"test"',))
    print('start a child process..')
    p.start()
    p.join()
    print('child process end.')

def testing3():
    print('Process (%s) is running...' % os.getpid())
    p = Pool(4) # here, 4 means you allow 4 subprocesses running at the same time
    for i in range(5):
        p.apply_async(task, args = (i,)) # subprocesses will start one by one
    print('Waiting for all subprocesses done...')
    p.close()
    p.join()
    print('All subprocesses done!')

if __name__ == '__main__':
    #testing1()
    #testing2()
    testing3()
