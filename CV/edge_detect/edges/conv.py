#!usr/bin/env python
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
import numpy as np

def conv2d(img, f):
    res = np.zeros_like(img).astype(np.float)
    img = img.astype(np.float)
    f = f.astype(np.float)

    img_h, img_w = img.shape
    f_h, f_w = f.shape

    def boardext(i, j, cont):
        if (i - cont < 0) or \
           (j - cont < 0) or \
           (i + cont >= img_h) or \
           (j + cont >= img_w):
            return True
        else:
            return False

    try:
        assert f_h % 2 == 1
    except Exception as e:
        print("Size Error :: Input Odd filter to this function!")

    f_cont = np.int((f_h - 1) / 2)
    for i in range(img_h):
        for j in range(img_w):
            if boardext(i,j,f_cont):
                res[i][j] = 0.
            else:
                res[i][j] = (f * img[(i-f_cont):(i+f_cont+1), (j-f_cont):(j+f_cont+1)]).sum()

    return res
