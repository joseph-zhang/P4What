#!usr/bin/env python
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from .conv import conv2d
import numpy as np

def build_gaussian_kernel(shape, sigma):
    m, n = [(ss-1.)/2. for ss in shape]
    x, y = np.mgrid[-m:m+1, -n:n+1]
    sigma = sigma**2
    k = 2*np.exp(-0.5 * (x**2 + y**2) / sigma)
    k = k / np.sum(k)
    return k

def gaussian(img, shape=(5,5), sigma=1.4):
    gaussian_f = build_gaussian_kernel(shape=shape, sigma=sigma)
    return conv2d(img, gaussian_f)

def susan(input_image, sim_threshold):
    img_h, img_w = input_image.shape
    res = gaussian(input_image)
    geo_threshold = 36

    for i in range(3, img_h-3):
        for j in range(3, img_w-3):
            usan_val = get_usan(input_image, i, j, sim_threshold)
            edge_response = (geo_threshold - usan_val) if geo_threshold - usan_val >= 0 else 0
            if edge_response == 0:
                res[i,j] = 0
            else:
                res[i,j] = 255
    return res

def get_usan(img, x, y, sim_threshold):
    offset_x = [-1, 0, 1,-2, -1, 0,
                1, 2,-3, -2, -1, 0,
                1, 2, 3,-3, -2, -1,
                0, 1, 2, 3,-3, -2,
                -1, 0, 1, 2, 3,-2,
                -1, 0, 1, 2,-1, 0, 1]

    offset_y = [-3,-3,-3,-2,-2,-2,
                -2,-2,-1,-1,-1,-1,
                -1,-1,-1,0, 0, 0,
                0, 0, 0, 0,1, 1,
                1, 1, 1, 1, 1, 2,
                2, 2, 2, 2,3, 3, 3]

    offsets = np.array(list(zip(offset_x, offset_y)))
    sim_cnt = 0
    usan_val = 0.

    for offset in offsets:
        diff = np.float(np.int(img[x+offset[0], y+offset[1]]) - np.int(img[x,y]))
        if(np.abs(diff) < sim_threshold):
            sim_cnt = sim_cnt + 1
        else:
            pass

        comp = np.exp(-1*np.power(diff / sim_threshold, 6))
        usan_val += comp

    return usan_val

