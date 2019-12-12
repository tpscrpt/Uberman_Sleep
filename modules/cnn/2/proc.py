import time
from datetime import datetime
import numpy as np
import tensorflow as tf
from tensorflow import keras

#data = np.load('./data/data_clean.npy', allow_pickle=True)

# mission: create actual input vectors (m, 2000, 2)
# examples = np.ndarray((10, 50000, 2000, 2))

#examples = np.ndarray((50000, 2000, 2))
#print(data.shape)
# shift back labels by 2000

def post_proc():
  labels = np.load('./data/labels_clean.npy', allow_pickle=True)
  labels_shifted = labels[2000:402000]
  np.save('./data/labels_shifted.npy', labels_shifted)

def do_more(step=0):
  if step > 7:
    labels = np.load('./data/labels_clean.npy', allow_pickle=True)
    labels_shifted = labels[2000:452000]
    np.save('./data/labels_shifted.npy', labels_shifted)
    return

  step_up = 50000 * step
  for sample in range(2000, 52000):
    examples[sample - 2000] = data[step_up + sample - 2000: step_up + sample]

  np.save('./data/examples/' + str(step), examples)

  print(examples.shape, examples[0][100])
  do_more(step + 1)

#do_more()
post_proc()
#np.save('./data/examples/0', examples)
