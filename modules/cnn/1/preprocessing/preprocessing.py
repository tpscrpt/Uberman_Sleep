import time
from datetime import datetime
import numpy as np

data_times, heart_rate = np.loadtxt('../data/data_unclean.csv',
                                  delimiter=',',
                                  unpack=True,
                                  skiprows=1,
                                  dtype={'names': ('datetime',  'heart_rate'),
                                         'formats': ("S20", float)})
label_times, sentiment = np.loadtxt('../data/labels_unclean.csv',
                          usecols=(1,3),
                          delimiter=',',
                          unpack=True,
                          skiprows=1,
                          dtype={'names': ('tweet', 'sentiment'),
                                 'formats': ("S20", float)})

print(len(data_times), len(heart_rate), len(label_times), len(sentiment))
# 411799 411799 1029 1029

# Task: Create a loop which assigns sentiment based on time in day to data
#   Construct output array with timestamps, hr, sentiment

p = "%Y-%m-%d %H:%M:%S"
epoch = datetime(1970, 1, 1)

numerical_data_timestamps = []
numerical_label_timestamps = []

for data_timestamp in data_times:
  numerical_data_timestamps.append(int((datetime.strptime(data_timestamp.decode('UTF-8'), p)
                                   - epoch).total_seconds()))

for label_timestamp in label_times:
  numerical_label_timestamps.append(int((datetime.strptime(label_timestamp.decode('UTF-8').strip("\""), p)
                                   - epoch).total_seconds()))

clean = []

for data_timestamp in range(len(numerical_data_timestamps)):
  print(data_timestamp)

  hr = heart_rate[data_timestamp]
  timestamp = numerical_data_timestamps[data_timestamp]
  valid = 0

  for label_timestamp in range(valid, len(numerical_label_timestamps)):
    # find data_timestamp > label_timestamp, save l_t0 and l_t1
    # find if data_timestamp is closer to l_t0 or l_t1
    # assign sentiment of closest timestamp
    label_timestamp1 = numerical_label_timestamps[label_timestamp]
    label_timestamp2 = 0

    if label_timestamp +1 == len(numerical_label_timestamps):
        clean.append([timestamp, hr, sentiment[label_timestamp]])
        break
    else:
      label_timestamp2 = numerical_label_timestamps[label_timestamp +1]

    if label_timestamp2 > timestamp > label_timestamp1 :
      valid = label_timestamp
      if (timestamp - label_timestamp1) < (label_timestamp2 - timestamp):
        clean.append([timestamp, hr, sentiment[label_timestamp]])
      else:
        clean.append([timestamp, hr, sentiment[label_timestamp +1]])

      break

clean = np.array(clean)
print(clean.shape)
np.save('../data/cleaned', clean)
