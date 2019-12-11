import matplotlib.pyplot as plt
import numpy as np

clean_data = np.load('../data/cleaned.npy')

timestamp = clean_data[:, 0]
hr = clean_data[:, 1]
sentiment = clean_data[:, 2]

plt.plot(hr)
plt.plot(sentiment)
plt.show()
