#!usr/local/env python
#coding=utf-8
# In previous file, a simple threading usage was shown
# note that thread of python is limited because GIL lock
# sub-thread has a same blcok of memory, so some clock mechanisms are imported 
import time, threading

A_BIG_NUM = int(1e3)
balance = 0
lock = threading.Lock()

# just a procedure
def check_money(n):
    global balance
    balance = balance + n
    balance = balance - n

# running the threads
def run_thread(n):
    for i in range(A_BIG_NUM):
        lock.acquire()
        try:
            check_money(n)
        finally:
            lock.release()

t1 = threading.Thread(target = run_thread, args = (5,))
t2 = threading.Thread(target = run_thread, args = (8,))

# start both two threads
t1.start()
t2.start()

# block
t1.join()
t2.join()

print(balance)

    
