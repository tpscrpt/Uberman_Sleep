from datetime import datetime
import numpy as np

p = "%Y-%m-%d %H:%M:%S"
epoch = datetime(1970, 1, 1)

data_times, heart_rate = np.loadtxt('./data_unclean.csv',
                                  delimiter=',',
                                  unpack=True,
                                  skiprows=1,
                                  dtype={'names': ('datetime',  'heart_rate'),
                                         'formats': ("S20", float)})

timestamps = []

for data_timestamp in data_times:
  timestamps.append(int((datetime.strptime(data_timestamp.decode('UTF-8'), p)
                                   - epoch).total_seconds()))
high_res = []

for i in range(len(heart_rate)-1):
  diff = timestamps[i+1] - timestamps[i]
  if diff <= 5:
    high_res.append([diff, heart_rate[i]])

final = np.ndarray((len(high_res), 2))
final[:] = high_res
print(final.shape)
np.save('high_res_samples.npy', final)
