#Y = np.array([0.000000,1.000000,1.000000,1.000000,0.000000,0.000000,0.000000,1.000000,1.000000])
#AL = np.array([0.973919,0.999160,0.999371,0.998955,0.970456,0.940091,0.990949,0.999794,0.998982])
#dAL = - (np.divide(Y, AL) - np.divide(1 - Y, 1 - AL))
#print(dAL)

import numpy as np
from sklearn.neural_network import MLPClassifier

train_cleaned = np.loadtxt("output/train_cleaned.csv", dtype=float, skiprows=1, delimiter=',')
test_cleaned = np.loadtxt("output/test_cleaned.csv", dtype=float, skiprows=1, delimiter=',')

np.random.shuffle(train_cleaned)

dev_labels = train_cleaned[: int(train_cleaned.shape[0] * 0.2), 0]
train_labels = train_cleaned[int(train_cleaned.shape[0] * 0.2) :, 0]

dev_data = train_cleaned[: int(train_cleaned.shape[0] * 0.2), 1:]
train_data = train_cleaned[int(train_cleaned.shape[0] * 0.2) :, 1:]

test_data = test_cleaned[:, 1:]

assert(train_cleaned.shape[0] == dev_labels.shape[0] + train_labels.shape[0])
assert(train_cleaned.shape[0] == dev_data.shape[0] + train_data.shape[0])
assert(train_cleaned.shape[1] - 1 == dev_data.shape[1])
assert(train_cleaned.shape[1] - 1 == train_data.shape[1])
assert(train_cleaned.shape[1] - 1 == test_data.shape[1])

model = MLPClassifier((10, 10), max_iter=2000, solver='adam', learning_rate='constant', learning_rate_init=0.01)

model.fit(train_data, train_labels)

dev_predictions = model.predict(dev_data)

accuracy = np.sum((dev_predictions == dev_labels).astype(int)) / dev_predictions.shape[0]

print(f"Dev set Accuracy: {accuracy}")

model.max_iter = 600
model.fit(dev_data, dev_labels)

test_predictions = model.predict(test_data)

submission = np.ndarray((test_cleaned.shape[0], 2), dtype=int)
submission[:, 0] = test_cleaned[:, 0]
submission[:, 1] = test_predictions[:]

print(submission[: 10, :].T)

np.savetxt("output/py_mlp_submission.csv",
           submission,
           delimiter=',',
           fmt='%d',
           header='PassengerId,Survived',
           comments='')
