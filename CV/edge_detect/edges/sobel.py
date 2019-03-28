#!usr/bin/env python
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from .conv import conv2d
import numpy as np

# solution that use conv2d method
def sobel(img):
    sobel_x = np.array([[-1, 0, 1],
                        [-2, 0, 2],
                        [-1, 0, 1]])

    sobel_y = np.array([[-1, -2, -1],
                        [0, 0, 0],
                        [1, 2, 1]])
    edge_x = np.zeros_like(img).astype(np.float32)
    edge_y = np.zeros_like(img).astype(np.float32)

    edge_x = conv2d(img, sobel_x)
    edge_y = conv2d(img, sobel_y)

    edge_map = np.hypot(edge_x, edge_y)
    return edge_x, edge_y, edge_map
