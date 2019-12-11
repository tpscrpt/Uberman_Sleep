import numpy as np
import tensorflow as tf
from tensorflow import keras
from main import MaxNormalization, TCN

clean_data = np.load('../data/cleaned.npy')

### PROBLEM WITH DATA, CHECK IN PREPROCESSING AND FIND BACK VALUE ###
### ALSO PLEASE DRAW THE AXES JESUS ###

X = np.ndarray((clean_data.shape[0], 2))
X[:, 0] = clean_data[:, 0]
X[:, 1] = clean_data[:, 1] / np.amax(clean_data[:, 1])
Y = (clean_data[:, 2] > 0).astype(int) # sentiment vector normalized
print(X[100])
number_of_samples = X.shape[0]
mini_batch_size = 400
samples_per_example = 2000 # must be > mini_batch_size

# for every mini-batch available, run this loop (training)
for i in range(int(number_of_samples * 0.9 / mini_batch_size)):
  X_train = np.ndarray((mini_batch_size, samples_per_example, 2))

  # for every example of the mini-batch (400 examples), collect the last 2000 samples
  # X_train should be of size (400, 2000, 2)
  for j in range(mini_batch_size):
    X_train[j] = [timestamps[i + samples_per_example], hrs[i + samples_per_example]]
  Y_train = Y[i * mini_batch_size: mini_batch_size]

  if i == 0:
    tcn = TCN(DATA_SHAPE=(X_train.shape))
    tcn.add_encoder(True, X_train)
    tcn.add_encoder()
    tcn.add_decoder()
    tcn.flatten()
    tcn.dense()
    tcn.compile()

  model.fit(X_train, Y_train)

