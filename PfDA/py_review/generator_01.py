#!usr/local/env/ python
#coding:utf-8

# a list generating expression is a generator
# just like lazy idea, a value will be calculated only when you want to get it
def gener():
    L = [x**2 for x in range(5)]
    n = 1
    for val in L:
        print('the %d-pos value in list L are %d'%(n, val))
        n += 1
    return 'done\n'

# a function become a generator if 'yield' is used
# also lazy
def fib(max):
    n, a, b = 0, 0, 1
    while n < max:
        yield b
        a, b = b, a+b
        n += 1
    return 'done\n'

# gener()

fibgener = fib(10)
print(next(fibgener)) # 1
print(next(fibgener)) # 1
print(next(fibgener)) # 2
print(next(fibgener)) # 3

for val in fibgener: # 5, 8, 13, 21, 34, 55 
    print(val)


