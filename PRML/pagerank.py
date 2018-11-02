#!usr/bin/env python
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

#------------------------------------------------------------------------------------------------------------
#                                 Naive Implementation of Pagerank Algorithm
#------------------------------------------------------------------------------------------------------------
import numpy as np

class PR(object):
    def __init__(self, W):
        """
        The parameter W is weight matrix of the given graph
        W[i][j] is the weight of edge from node i to node j
        """
        self.W = W
        self.N = W.shape[1]

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
        r = np.random.rand(N)
        # iteration counter
        t = 0

        # do pagerank iteration until convergence
        # !! The loop will be slow, a more efficient version should be implemented with vectorization !!
        while True:
            last_r = np.zeros(N)
            for i in range(N):
                for j in range(N):
                    last_r[j] = last_r[j] + r[i] * (self.W[i][j] / np.sum(W[i]))
            for p in range(N):
                last_r[p] = last_r[p] * d + (1 - d) / N
            if np.linalg.norm(r - last_r, 2) < eps:
                break
            else:
                r = last_r
                if info: print("Iter {}: r = {}".format(t, r))
                t = t + 1
        return r

# Test algorithm
if __name__ == "__main__":
    # test weight matrix
    W = np.array([
        [1., 1., 0.],
        [1., 0., 1.],
        [0., 0., 1.]
    ])

    # do pagerank
    pagerank = PR(W)
    r = pagerank.getRank(info=True)

    # result rank list of N nodes on graph
    print("Rank of nodes: {}".format(r))
