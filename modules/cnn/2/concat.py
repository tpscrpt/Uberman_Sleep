import numpy as np

fp = np.memmap('./data/data_concat.npy', dtype=float, mode='w+', shape=(450000, 2000, 2))

for i in range(8):
  data = np.load('./data/examples/' + str(i) + '.npy')
  fp[i*50000: i*50000 + 50000] = data
  print(i)

print(fp.shape)
print(fp[474747][0])
del fp

newfp = np.memmap('./data/data_concat.npy', dtype=float, mode='r', shape=(450000, 2000, 2))
print(fp[474747][0])

del newfp
