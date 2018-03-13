# tensorflow - minist standard example
# __init__.py

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

__all__ = {'mnist_eval', 'mnist_inference', 'mnist_train'}

from . import mnist_inference
from . import mnist_train
