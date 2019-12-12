import time
from datetime import datetime
import numpy as np
import tensorflow as tf
from tensorflow import keras

data_orig = np.loadtxt
#data = np.load('./data/examples/0.npy', allow_pickle=True)
#data2 = np.load('./data/examples/1.npy', allow_pickle=True)
labels = np.load('./data/labels_shifted.npy', allow_pickle=True)

"""
data_times, heart_rate = np.loadtxt('./data/data_unclean.csv',
                                  delimiter=',',
                                  unpack=True,
                                  skiprows=1,
                                  dtype={'names': ('datetime',  'heart_rate'),
                                         'formats': ("S20", int)})
"""
label_times, sentiment = np.loadtxt('./data/labels_unclean.csv',
                          usecols=(1,3),
                          delimiter=',',
                          unpack=True,
                          skiprows=1,
                          dtype={'names': ('tweet', 'sentiment'),
                                 'formats': ("S20", int)})
def verify():
  # print(heart_rate[55028], data2[5000][28]) PASS

verify()
