#!usr/local/env python
#coding=utf-8
# In previous file, a simple threading usage was shown
# note that thread of python is limited because GIL lock
# sub-thread has a same blcok of memory, so some clock mechanisms are imported
# Exclusive lock!
import time, threading

A_SMALL_NUM = 10
A_BIG_NUM = 100

balance = 0
lock = threading.Lock()

# just a procedure
def check_money(n):
    global balance
    balance = balance + n
    balance = balance - n

# running the threads
def run_thread(n, num):
    for i in range(num):
        lock.acquire()
        try:
            check_money(n)
            time.sleep(0.1)
        finally:
            lock.release()
    print('%s done'%(threading.current_thread().name))

# running the threads-ver2
def run_thread2(n, num):
    for i in range(num):
        check_money(n)
        time.sleep(0.1)
    print('%s done'%(threading.current_thread().name))

t1 = threading.Thread(target = run_thread2, args = (5, A_BIG_NUM))
t2 = threading.Thread(target = run_thread2, args = (8, A_SMALL_NUM))

# start both two threads
t1.start()
t2.start()


# block
#t1.join()
t2.join()

print(balance)
