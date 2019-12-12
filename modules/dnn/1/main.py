import numpy as np
from tensorflow import keras
from keras.layers import *

def model(input_shape, batch_size, dense):
  layers = [
    Dense(dense[0], input_shape=input_shape, batch_size=batch_size, activation='relu'),
    BatchNormalization(),
    Dense(1, activation='sigmoid')]
  ]

  for i in range(len(dense[1:])):
    layers.insert(i + 2, Dense(dense[1:][i], activation='relu'))

"""

Considering the Uberman schedule is the target, the highest
resolution should be 4 hours because it doesn't account for mistakes

A resolution for the last hour may indicate a more local pattern for the
heart based on recent activities

Continuing in this line, a 15 minute resolution is of order and so are a
4 minute resolution, a 60 second resolution and a 15 second resolution

Two formulas should be implemented to calculate the HRV, one for
timespace and the other for frequency.

The ema formula will be the same for a given resolution (HR and HRV
share params)

"""
