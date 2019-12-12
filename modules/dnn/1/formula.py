import numpy as np
import matplotlib.pyplot as plt

def linear_weight_moving_average(signal, period):
    buffer = [np.nan] * period
    for i in range(period, len(signal)):
        buffer.append(
            (signal[i - period : i] * (np.arange(period) + 1)).sum()
            / (np.arange(period) + 1).sum()
        )
    return buffer

data = np.load('./high_res_samples.npy', allow_pickle=True)

print(data.shape, data[100])

sampling_rate = 0.2

resolutions = [
  [3600 * 4 * sampling_rate], # 4 hours
  [3600 * sampling_rate],     # 1 hour
  [900 * sampling_rate],      # 15 minutes
  [240 * sampling_rate],      # 4 minutes
  [60 * sampling_rate],       # 1 minute
  [15 * sampling_rate],       # 15 seconds
]

plt.plot(data[-40:])
for i in range(len(resolutions)):
  res = int(resolutions[i][0])
  out = linear_weight_moving_average(data[:, 1], res)
  resolutions[i].append(out)
  plt.plot(out[-40:])

plt.show()


