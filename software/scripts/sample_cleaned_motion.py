import numpy as np

data = np.loadtxt('../reference/ojwalch/sleep_classifiers/outputs/cropped/1066528_cleaned_motion.out')

data = data[: int(len(data) / 10)]

np.savetxt('../preprocessing/samples/motion.csv', data, fmt="%.5f", delimiter=',')
