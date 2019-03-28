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

def gradient(img_blur):
    sobel_x = np.array([[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]], dtype='float')
    sobel_y = np.array([[1, 2, 1], [0, 0, 0], [-1, -2, -1]], dtype='float')

    dx = conv2d(img_blur, sobel_x)
    dy = conv2d(img_blur, sobel_y)

    return np.hypot(dx, dy), np.arctan2(dy, dx)

def assign_angle(theta):
    angle = np.rad2deg(theta) % 180
    if (0 <= angle < 22.5) or (157.5 <= angle <= 180):
        angle = 0
    elif (22.5 <= angle < 67.5):
        angle = 45
    elif (67.5 <= angle < 112.5):
        angle = 90
    elif (112.5 <= angle < 157.5):
        angle = 135
    return angle

def sps(grad, theta):
    grad_h, grad_w = grad.shape
    res = np.zeros_like(grad)

    for i in range(1,grad_h-1):
        for j in range(1,grad_w-1):
            ct_angle = assign_angle(theta[i,j])
            if ct_angle == 0:
                if (grad[i,j] >= grad[i,j-1]) and (grad[i,j] >= grad[i,j+1]):
                    res[i,j] = grad[i,j]
                else:
                    pass
            elif ct_angle == 90:
                if (grad[i,j] >= grad[i-1,j]) and (grad[i,j] >= grad[i+1,j]):
                    res[i,j] = grad[i,j]
                else:
                    pass
            elif ct_angle == 135:
                if (grad[i,j] >= grad[i-1,j-1]) and (grad[i,j] >= grad[i+1, j+1]):
                    res[i,j] = grad[i,j]
                else:
                    pass
            elif ct_angle == 45:
                if (grad[i,j] >= grad[i-1,j+1]) and (grad[i,j] >= grad[i+1,j-1]):
                    res[i,j] = grad[i,j]
                else:
                    pass
            else:
                print("ct_angle: {}".format(ct_angle))
                raise RuntimeError("Angle Error!")

    return res

def threshold(sps_img, lower_t, upper_t):
    res = np.zeros_like(sps_img).astype(np.int32)
    strong_idx = sps_img > upper_t
    weak_idx = (sps_img >= lower_t) & (sps_img <= upper_t)
    board_idx = sps_img < lower_t

    res[strong_idx] = 255
    res[weak_idx] = 50
    res[board_idx] = 0

    return res

def post_opt(th_img):
    res = th_img.copy()
    img_h, img_w = th_img.shape
    weak_is, weak_js = np.where(th_img == 50)

    for i in range(weak_is.shape[0]):
        weak_i = weak_is[i]
        weak_j = weak_js[i]
        check_list = np.array([th_img[weak_i+1,weak_j], th_img[weak_i-1,weak_j],
                               th_img[weak_i,weak_j+1], th_img[weak_i,weak_j-1],
                               th_img[weak_i-1,weak_j-1], th_img[weak_i+1,weak_j+1],
                               th_img[weak_i-1,weak_j+1], th_img[weak_i+1,weak_j-1]])
        if(np.all(check_list == 255)):
            res[weak_i, weak_j] = 255
        else:
            res[weak_i, weak_j] = 0

    return res

def canny(img, lower_t, upper_t):
    img_blur = gaussian(img)
    grad, theta = gradient(img_blur)
    sps_img = sps(grad, theta)
    th_img = threshold(sps_img, lower_t, upper_t)
    edge_map = post_opt(th_img)
    return [img_blur, grad, sps_img, th_img, edge_map]
