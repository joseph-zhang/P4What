#!usr/bin/env python
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import os
import sys
import edges
import argparse
import numpy as np
from tqdm import tqdm
from PIL import Image
import matplotlib.image as mpimg

parser = argparse.ArgumentParser()
parser.add_argument("--img_path", type=str, required=True, help="the original image dir")
parser.add_argument("--out_path", type=str, required=True, help="the target image dir")
parser.add_argument("--method", type=str, required=True, help="the method of edge detection process.")
args = parser.parse_args()

method_candidate = ["sobel", "marr", "canny", "susan"]

def load_image_data(filename, mode="L"):
    # load image as an PIL image
    file_path = os.path.join(args.img_path, filename)
    img = Image.open(file_path).convert(mode)
    return np.array(img)

def save_image_data(image, filename):
    # save target image
    if not os.path.exists(args.out_path):
        os.makedirs(args.out_path)

    save_path = os.path.join(args.out_path, filename)
    image = image.astype(np.uint8)
    mpimg.imsave(save_path, image, cmap="gray")

if __name__ == "__main__":
    img_names = os.listdir(args.img_path)

    try:
        assert img_names != []
    except Exception as e:
        print("DO NOTHING :: Img dir is empty!")

    try:
        assert args.method in method_candidate
    except Exception as e:
        print("BAD VALUE :: Unkown detection method!")

    for img_name in tqdm(img_names):
        img = load_image_data(img_name)
        ext_img_name, _ = os.path.splitext(img_name)
        out_name = ext_img_name + ".png"

        if args.method == "sobel":
            edge_x, edge_y, edge_map = edges.sobel(img)
            save_image_data(edge_x, "sobel_edge_x_" + out_name)
            save_image_data(edge_y, "sobel_edge_y_" + out_name)
            save_image_data(edge_map, "sobel_edge_map_" + out_name)
        elif args.method == "marr":
            edge_map, filtered_img = edges.marr(img)
            save_image_data(edge_map, "marr_edge_map_" + out_name)
            save_image_data(filtered_img, "marr_LoG_map_" + out_name)
        elif args.method =="canny":
            img_blur, grad, sps_img, th_img, edge_img = edges.canny(img, lower_t=3, upper_t=25)
            save_image_data(img_blur, "canny_gaussian_map_" + out_name)
            save_image_data(grad, "canny_grad_map_" + out_name)
            save_image_data(sps_img, "canny_sps_map_" + out_name)
            save_image_data(th_img, "canny_threshold_map_" + out_name)
            save_image_data(edge_img, "canny_edge_map_" + out_name)
        elif args.method =="susan":
            edge_map = edges.susan(img, sim_threshold=36)
            save_image_data(edge_map, "susam_edge_map_" + out_name)
        else:
            pass

    print("{} process done!".format(args.method))
