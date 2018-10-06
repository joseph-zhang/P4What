#!usr/local/env python

## As the first-class-object, we can write a function to wrap a function so that it can do more things.
## The first function is called decorator, and the second one is what we want to decorate.

# function as return value
# define a function to produce an adder, which can add the value x to its input number
def adder(x):
    def addx(val):
        return val+x
    return addx

# create some adder
adder1 = adder(1)
adder2 = adder(2)

# use them now
print(adder1(5)) # ==> 6
print(adder2(5)) # ==> 7

#### Now if we want to add some more abilities to an exist function,
## for example, some log information, what about time?
import time

# now here is a function that cost a lot
def heavy():
    time.sleep(1.5)

# call this function, the terminal holds 1.5s
heavy()
print("heavy over.\n")
# now if we want to get the log of time without modified the function `heavy`
# write a decorator!
def heavy_decorator(func):
    def log_time():
        startTime = time.time()
        func()
        print("time delay: {}".format(time.time() - startTime))
    return log_time

# decorate original funtion
heavy = heavy_decorator(heavy)

# call this function again
heavy() # ==> time delay: 1.5017609596252441
print("heavy over.\n")

# actually, we need not assign the decorator explicitly
# now we write another decorator
def overinfo_decorator(func):
    def log_over():
        func()
        print("function over.\n")
    return log_over

@overinfo_decorator
def heavy():
    time.sleep(1.5)

# call original function
heavy() # ==> function over.

# however, we want to print the function name, write the decorator again
def overinfo_decorator(func):
    def log_over():
        func()
        print("{} over.\n".format(func.__name__))
    return log_over

@overinfo_decorator
def heavy():
    time.sleep(1.5)

# call original function
heavy() # ==> heavy over.

## Now everything is good, but if we do this
print(heavy.__name__) # ==> log_over
# the name of function heavy is not heavy itself, but log_over!
# because what we actual used is log_over

# how to hold the consistency?
# use function tools
from functools import wraps
def overinfo_decorator(func):
    @wraps(func)
    def log_over():
        func()
        print("{} over.\n".format(func.__name__))
    return log_over

@overinfo_decorator
def heavy():
    time.sleep(1.5)

# check function name again
print(heavy.__name__) # ==> heavy

## We need not to remember all the things, just understand the first-class-object
## and the decorator is just a syntactic sugar, we can implement it by ourselves.
