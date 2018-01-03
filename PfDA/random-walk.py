# this is the example about random in ch. 4
# the first implement is native python 
import numpy as np
from numpy.random import randn
import matplotlib.pyplot as plt

nsteps = 1000
draws = np.random.randint(0,2,size = nsteps)
steps = np.where(draws>0,1,-1)
walk = steps.cumsum()
fig = plt.figure()
ax = fig.add_subplot(1,1,1)
ax.plot(walk)
fig.savefig('test.png')