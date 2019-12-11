import time
import numpy as np

data_times, heart_rate = np.loadtxt('./data/data_unclean.csv',
                                  delimiter=',',
                                  unpack=True,
                                  skiprows=1,
                                  dtype={'names': ('datetime',  'heart_rate'),
                                         'formats': (str, float)})
label_times, sentiment = np.loadtxt('./data/labels_unclean.csv',
                          usecols=(1,3),
                          delimiter=',',
                          unpack=True,
                          skiprows=1,
                          dtype={'names': ('tweet', 'sentiment'),
                                 'formats': (str, float)})

print(len(data_times), len(heart_rate), len(label_times), len(sentiment))
# 411799 411799 1029 1029

