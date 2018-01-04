# this is the example about random in ch. 4
# the first implement is native python 
import numpy as np
from numpy.random import randn
import matplotlib.pyplot as plt

# simple numpy example of random walk
nsteps = 1000
draws = np.random.randint(0,2,size = nsteps)
steps = np.where(draws>0,1,-1)
walk = steps.cumsum()
fig = plt.figure()
ax = fig.add_subplot(1,1,1)
ax.plot(walk)
fig.savefig('test.png')

# ------------------ other implementations --------------------
# these code can be verified in interactive environment or ipython

# native implementation
position = 0
walk = [position]
steps = 1000
for i in xrange(steps):
  step = 1 if random.randint(0,1) else -1
  position += step
  walk.append(position)
  
# more complex example, multiple random walks
nwalks = 5000
nsteps = 1000
draws = np.random.randint(0,2,size(nwalks, nsteps))
walks = steps.cumsum(1)
