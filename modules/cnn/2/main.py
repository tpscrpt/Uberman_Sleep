import time
from datetime import datetime
import numpy as np
import tensorflow as tf
from tensorflow import keras

data = np.load('./data/data_clean.npy', allow_pickle=True)
labels = np.load('./data/labels_clean.npy', allow_pickle=True)

model = keras.Sequential([
  keras.layers.Conv1D(32, 4, strides=1, input_shape=(2000,2), batch_size=400),
  keras.layers.Activation('relu', a=0.01),
  keras.layers.BatchNormalization(),
  keras.layers.Maxpooling1D(2, 2),
  keras.layers.Conv1D(64, 4, strides=1),
  keras.layers.Activation('relu', a=0.01),
  keras.layers.BatchNormalization(),
  keras.layers.Maxpooling1D(2, 2),
  keras.layers.Upsampling1D(2),
  keras.layers.Conv1D(96, 4, strides=1),
  keras.layers.Activation('relu', a=0.01),
  keras.layers.BatchNormalization(),
  keras.layers.Flatten(),
  keras.layers.Dense(512)
  keras.layers.Activation('relu', a=0.01),
  keras.layers.Dense(512)
  keras.layers.Activation('relu', a=0.01),
  keras.layers.Dense(1, activation='sigmoid')
])

callbacks = [
  keras.callbacks.callbacks.ModelCheckpoint('models/', monitor='val_acc', verbose=0, save_best_only=True, mode='auto', period=3)
  keras.callbacks.callbacks.EarlyStopping(monitor='val_acc', min_delta=0.001, patience=0, verbose=0, mode='auto', restore_best_weights=False)
]

model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])

model.fit(X_train, Y_train, validation_split=0.1)
