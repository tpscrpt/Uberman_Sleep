import numpy as np
from sklearn.linear_model import LogisticRegression

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

model = LogisticRegression(
    penalty='l2',
    solver='lbfgs',
    max_iter=800
)

model.fit(train_data, train_labels)

dev_predictions = model.predict(dev_data)

accuracy = np.sum((dev_predictions == dev_labels).astype(int)) / dev_predictions.shape[0]

print(f"Dev set Accuracy: {accuracy}")

model.max_iter = 200
model.fit(dev_data, dev_labels)

print(model.coef_)
test_predictions = model.predict(test_data)

submission = np.ndarray((test_cleaned.shape[0], 2), dtype=int)
submission[:, 0] = test_cleaned[:, 0]
submission[:, 1] = test_predictions[:]

print(submission[: 10, :].T)

np.savetxt("output/submission.csv",
           submission,
           delimiter=',',
           fmt='%d',
           header='PassengerId,Survived',
           comments='')
