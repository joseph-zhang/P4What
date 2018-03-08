# This is an example of cs231n lecture 2
# KNN for CIFAR10, source code can also be found in lecture
# Note that CIFAR10 dataset fold locates in ~/  

import sys, os
import numpy as np
import matplotlib.pyplot as plt
from scipy.misc import imread
from collections import Counter

try:
    import cPickle as pickle
except:
    import pickle

def load_CIFAR_batch(batch_path):
#the function to load one of six batches
    # open the python form data batch file
    with open(batch_path,'rb') as fo:
        thedict = pickle.load(fo,encoding='latin1') # transfer it to python data structure
    images = thedict['data']; # get image data as numpy array (1000,3072)
    labels = thedict['labels']; # get lables as python list which range in [0,9]

    images = images.reshape(10000,3,32,32).transpose(0,2,3,1).astype('float'); # note that the method transpose is important
    labels = np.array(labels);
    return (images,labels)

def load_CIFAR10(root_path):
# the function excute load_CIFAR_batch procedure to load all datas in CIFAR10
    batches = []
    batch_labels = []
    # add all 1 to 5 batches 
    for i in range(1,6):
        batch_path = os.path.join(root_path,'data_batch_%d' %(i));
        d1,d2 = load_CIFAR_batch(batch_path);
        batches.append(d1);
        batch_labels.append(d2);
    # now we concat all 5 batches to create tranning set
    Xtr = np.concatenate(batches);
    Ytr = np.concatenate(batch_labels);
    # and deal with test batch
    Xte, Yte = load_CIFAR_batch(os.path.join(root_path,'test_batch'));
    return Xtr,Ytr,Xte,Yte
