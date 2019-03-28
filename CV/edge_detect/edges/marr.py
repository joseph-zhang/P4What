#!usr/bin/env python
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from .conv import conv2d
import numpy as np


def build_LoG_kernel(shape, sigma):
    m, n = [(ss-1.)/2. for ss in shape]
    y, x = np.ogrid[-m:m+1,-n:n+1]
    f = np.exp(-(x*x + y*y) / (2.*sigma*sigma))
    f = f / f.sum()
    f = f * (x*x + y*y - 2*sigma**2) / sigma**4
    return f - f.mean()

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

def marr(img, shape=(11,11), sigma=1.4):
    img_h, img_w = img.shape
    LoGfilter = build_LoG_kernel(shape=shape, sigma=sigma)
    img_blur = gaussian(img)
    threshold = 0.04 * np.std(img_blur, ddof=1)
    filtered_img = conv2d(img, LoGfilter)
    res = np.zeros_like(img).astype(np.int32)
    cont = np.int((LoGfilter.shape[0] - 1) / 2)

    for i in range(cont, img_h - cont - 1):
        for j in range(cont, img_w - cont - 1):
            if (np.sign(filtered_img[i, j-1]) * np.sign(filtered_img[i, j+1])) < 0 or \
               (np.sign(filtered_img[i-1, j]) * np.sign(filtered_img[i+1, j])) < 0:
                if np.std(img_blur[(i-cont):(i+cont+1), (j-cont):(j+cont+1)], ddof=1) > threshold:
                    res[i,j] = 255

    return res, filtered_img
