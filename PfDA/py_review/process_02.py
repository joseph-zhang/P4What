#!usr/bin/env python
#coding=utf-8
# since the simple multiprocessing usage has been shown
# here is an example of 'subprocess' to control a outer process
import subprocess
import multiprocessing
import time, os

# just execute a simple one-line command
def testing1():
    print('run "$ nslookup www.metaphia.moe" in a process')
    r = subprocess.call(['nslookup', 'www.metaphia.moe'])
    print('Exit code', r)

# control input and output of a process 
def testing2():
    print('run "$ nslookup" in a process')
    p = subprocess.Popen(['nslookup'],
                         stdin = subprocess.PIPE,
                         stdout = subprocess.PIPE,
                         stderr = subprocess.PIPE)
    output_info, error_info = p.communicate(b'set q=mx\nwww.metaphia.moe\nexit\n')
    
    print('output infomation is ', output_info.decode('utf-8'))
    print('error information is ', error_info.decode('utf-8'))
    print('Exit code is ', p.returncode)

if __name__ == '__main__':
    testing1()
    #testing2()
