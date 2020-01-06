import numpy as np
import pandas as pd

# 0 PassengerId,
# 1 Survived,
# 2 Pclass,
# 3 Sex (male = 0, female = 1),
# 4 Age,
# 5 SibSp,
# 6 Parch,
# 7 Fare

training_data = pd.read_csv('../data/train.csv',
                          quotechar='"',
                          skipinitialspace=True,
                          delimiter=',',
                          skiprows=0,
                          usecols=[0, 1, 2, 4, 5, 6, 7, 9],
).as_matrix()


training_data[:, 3] = (training_data[:, 3] == 'female').astype(int)

training_data = training_data.astype(float)
training_data = training_data[np.all(np.isfinite(training_data), axis=1)]
training_data[:, 2] = training_data[:, 2] / training_data[:, 2].max()
training_data[:, 4] = training_data[:, 4] / training_data[:, 4].max()
training_data[:, 5] = training_data[:, 5] / training_data[:, 5].max()
training_data[:, 6] = training_data[:, 6] / training_data[:, 6].max()
training_data[:, 7] = training_data[:, 7] / training_data[:, 7].max()

np.savetxt("../output/train_cleaned.csv",
           training_data,
           delimiter=',',
           header='"PassengerId","Survived","Pclass","Sex","Age","SibSp","Parch","Fare"',
           fmt="%1.5f")

test_data = pd.read_csv('../data/train.csv',
                          quotechar='"',
                          skipinitialspace=True,
                          delimiter=',',
                          skiprows=0,
                          usecols=[0, 1, 2, 4, 5, 6, 7, 9],
).as_matrix()


test_data[:, 3] = (test_data[:, 3] == 'female').astype(int)
test_data = test_data.astype(float)
test_data = test_data[np.all(np.isfinite(test_data), axis=1)]
test_data[:, 2] = test_data[:, 2] / test_data[:, 2].max()
test_data[:, 4] = test_data[:, 4] / test_data[:, 4].max()
test_data[:, 5] = test_data[:, 5] / test_data[:, 5].max()
test_data[:, 6] = test_data[:, 6] / test_data[:, 6].max()
test_data[:, 7] = test_data[:, 7] / test_data[:, 7].max()


np.savetxt("../output/test_cleaned.csv",
           test_data,
           delimiter=',',
           header='"PassengerId","Survived","Pclass","Sex","Age","SibSp","Parch","Fare"',
           fmt="%1.5f")