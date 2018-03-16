#!usr/local/env python
#coding:utf-8
import threading, time

def loopn(n):
    print('Thred %s is running..' %(threading.current_thread().name))
    for i in range(n):
        print('Thred %s is running..' %(threading.current_thread().name), i)
        time.sleep(1)
    print('Thread %s is ended.' %(threading.current_thread().name))


print('Thred %s is running..' %(threading.current_thread().name))
t = threading.Thread(target = loopn, args = (5,), name = 'LoopThread')
t.start()
t.join() # here, MainThread is blocked
print('Thred %s is ended.' %(threading.current_thread().name))
