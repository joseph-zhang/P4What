# here is the main procedure to manipulate cifar10
# classification with KNN method
from cs231n.csuti.cifarload import load_CIFAR10
from cs231n.KNN.cifarKNN import *
import pdb
# the root path of cifar 10 dataset
cifar_path = '../dataset/cifar-10-batches-py/'

# load cifar10 data
Xtr, Ytr, Xte, Yte = load_CIFAR10(cifar_path)
print 'Training data Xtr: ', Xtr.shape
print 'Training labels Ytr: ', Ytr.shape
print 'Test data Xte: ', Xte.shape
print 'Test labels Yte: ', Yte.shape

# flatten out all images to be one-dimensional
Xtr_rows = Xtr.reshape(Xtr.shape[0], 32*32*3)
Xte_rows = Xte.reshape(Xte.shape[0], 32*32*3)

# cross validation settings
# number of data folds
num_folds = 5

# set the number of k
ks = [1, 3, 5, 8, 10, 12, 15, 20, 50, 100]

# split the training data 
Xtr_folds = np.array_split(Xtr_rows, num_folds, axis = 0)
Ytr_folds = np.array_split(Ytr, num_folds, axis = 0)

# acc log, a dict
acc_rate = {}

def warp(x):
    if not type(x) is list:
        return [x]
    else: return x
    
for i in range(num_folds):
    # create training set and validation set
    curr_Xtr = np.concatenate(warp(Xtr_folds[0:i+1]) + (warp(Xtr_folds[i+1:num_folds])))
    curr_Ytr = np.concatenate(warp(Ytr_folds[0:i+1]) + (warp(Ytr_folds[i+1:num_folds])))
    #curr_Ytr = np.concatenate((Ytr_folds[0:i+1], Ytr_folds[i+1:num_folds]))
    curr_Xvali = Xtr_folds[i]
    curr_Yvali = Ytr_folds[i]
    #pdb.set_trace()
    # create knn object
    knn = KNNer()
    knn.train(curr_Xtr,curr_Ytr)

    # check accuracy for every k choice
    for k in ks:
        print 'predicting: fold-%d, k=%d...' %(i,k)
        y_pred = knn.predict(curr_Xvali, k = k)
        accuracy = np.mean(y_pred == curr_Yvali)
        
        if i == 0:
            acc_rate[k] = []
        acc_rate[k].append(accuracy)
        print 'fold = %d, k = %d, acc = %f' %(i, k, accuracy)



