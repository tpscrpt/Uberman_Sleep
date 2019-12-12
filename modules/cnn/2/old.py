import time
from datetime import datetime
import numpy as np
import tensorflow as tf
from tensorflow import keras

# in one file because I just suck at python atm
import time
from datetime import datetime
import numpy as np

data_times, heart_rate = np.loadtxt('./data/data_unclean.csv',
                                  delimiter=',',
                                  unpack=True,
                                  skiprows=1,
                                  dtype={'names': ('datetime',  'heart_rate'),
                                         'formats': ("S20", int)})
label_times, sentiment = np.loadtxt('./data/labels_unclean.csv',
                          usecols=(1,3),
                          delimiter=',',
                          unpack=True,
                          skiprows=1,
                          dtype={'names': ('tweet', 'sentiment'),
                                 'formats': ("S20", int)})

p = "%Y-%m-%d %H:%M:%S"
epoch = datetime(1970, 1, 1)

data_timestamps = []
label_timestamps = []

# generate shape: (m, 2000, nx)
for data_timestamp in data_times:
  data_timestamps.append(int((datetime.strptime(data_timestamp.decode('UTF-8'), p)
                                   - epoch).total_seconds()))

for label_timestamp in label_times:
  label_timestamps.append(int((datetime.strptime(label_timestamp.decode('UTF-8').strip("\""), p)
                                   - epoch).total_seconds()))

clean_X = np.ndarray((len(data_timestamps), 2))
clean_Y = np.ndarray((len(data_timestamps), 1))

for i in range(len(data_timestamps)):

  hr = heart_rate[i]
  timestamp = data_timestamps[i]
  diff = 0
  valid = 0

  if i == 0:
    diff = data_timestamps[i+1] - timestamp
  else:
    diff = timestamp - data_timestamps[i-1]

  for j in range(valid, len(label_timestamps)):
    # find data_timestamp > label_timestamp, save l_t0 and l_t1
    # find if data_timestamp is closer to l_t0 or l_t1
    # assign sentiment of closest timestamp
    label_timestamp1 = label_timestamps[j]
    label_timestamp2 = 0

    if j + 1 == len(label_timestamps):
        clean_X[i] = [diff, hr]
        clean_Y[i] = sentiment[j]
        break
    else:
      label_timestamp2 = label_timestamps[j + 1]

    if label_timestamp2 > timestamp > label_timestamp1:
      valid = j
      if (timestamp - label_timestamp1) < (label_timestamp2 - timestamp):
        clean_X[i] = [diff, hr]
        clean_Y[i] = sentiment[j]
      else:
        clean_X[i] = [diff, hr]
        clean_Y[i] = sentiment[j+1]

      break

print(clean_X.shape, clean_Y.shape)
print(clean_X[100], clean_Y[100])
np.save('./data/data_clean', clean_X)
np.save('./data/labels_clean', clean_Y)
