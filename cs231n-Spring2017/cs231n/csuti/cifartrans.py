# the method to transfer cifar into training, validation, test and development data set
# after raw data have been processed by load_CIFAR10 procedure
from . import cifarload
import numpy as np

def cifar_trans(root_path, num_train = 49000, num_vali = 1000, num_test = 1000, num_dev = 500):
    # split the data set
    X_tr, y_tr, X_te, y_te = cifarload.load_CIFAR10(root_path)
    mask = range(num_train, num_train + num_vali)
    X_vali = X_tr[mask]
    y_vali = y_tr[mask]
    mask = range(num_train)
    X_train = X_tr[mask]
    y_train = y_tr[mask]
    mask = range(num_test)
    X_test = X_te[mask]
    y_test = y_te[mask]
    mask = np.random.choice(num_train, num_dev, replace=False)
    X_dev = X_tr[mask]
    y_dev = y_tr[mask]

    # reshape them to rows
    X_train = np.reshape(X_train, (X_train.shape[0], -1))
    X_vali = np.reshape(X_vali, (X_vali.shape[0], -1))
    X_test = np.reshape(X_test, (X_test.shape[0], -1))
    X_dev = np.reshape(X_dev, (X_dev.shape[0], -1))

    # processing: subtract mean image
    sets = [X_train, X_vali, X_test, X_dev]
    mean_image = np.mean(X_train, axis = 0)
    for i in range(len(sets)):
        sets[i] -= mean_image

    # add bias dimension and transform into columns
    X_train = np.hstack([X_train, np.ones((X_train.shape[0], 1))])
    X_test = np.hstack([X_test, np.ones((X_test.shape[0], 1))])
    X_vali = np.hstack([X_vali, np.ones((X_vali.shape[0], 1))])
    X_dev = np.hstack([X_dev, np.ones((X_dev.shape[0], 1))])

    return X_train, y_train, X_vali, y_vali, X_test, y_test, X_dev, y_dev
