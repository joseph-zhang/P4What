#!usr/bin/env python
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

#------------------------------------------------------------------------------------------------------------
#                                 Vectorized Implementation of Pagerank Algorithm
#------------------------------------------------------------------------------------------------------------
import numpy as np

class PR(object):
    def __init__(self, W):
        """
        The parameter W is the probability matrix of the given graph
        W[i][j] is the probability of edge from node i to node j
        """
        self.W = W
        self.N = W.shape[1]
        self.Wt = np.mat(self.W).T

    def getRank(self, eps = 1.0e-8, d = 0.85, info = False):
        """
        The method to get the rank of N input nodes
        --------------------------
        eps : the value of control iteration precision
        d : damping factor
        info : to print iteration information or not
        --------------------------
        return a N-dim np-array r which meets sum(r) = 1.0
        """
        N = self.N

        # initialize rank list
        r = np.mat(np.ones(N)).T / N
        # iteration counter
        t = 0

        # define auxiliary matrix
        B = np.mat(np.ones((N, N))) / N
        M = d * self.Wt + (1-d) * B
        last_r = r.copy()

        # do pagerank iteration until convergence
        while True:
            last_r = M*last_r
            if np.linalg.norm(r - last_r, 2) < eps:
                break
            else:
                r = last_r
                if info: print("Iter {}: r = {}".format(t, r.getA().squeeze()))
                t = t + 1
        return r.getA().squeeze()

# --------------------------------- Test algorithm ---------------------------------
# Showing the first example in this website:
# http://pi.math.cornell.edu/~mec/Winter2009/RalucaRemus/Lecture3/lecture3.html
if __name__  == "__main__":
    # test weight matrix
    W = np.array([
        [0.0,  1./3, 1./3, 1./3],
        [0.0,   0.0, 1./2, 1./2],
        [1.0,   0.0,  0.0,  0.0],
        [1./2,  0.0, 1./2,  0.0]
    ])

    # do pagerank
    pagerank = PR(W)
    r = pagerank.getRank(d=1, info=True)

    # result rank list of N nodes on graph
    print("Rank of nodes: {}".format(r))
