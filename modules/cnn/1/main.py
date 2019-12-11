import numpy as np
import tensorflow as tf
from tensorflow import keras

"""
Basis: heart-rate variability
Evaluation: time-series over 4 hours at 0.2Hz
Criteria: binary classification (asleep, awake)
---------
Data
X.shape = (m, 2880, 1)
Y.shape = (m, 1)
---------
ENCODER:
  - Kernel on 1D kept small despite number of samples per example because
  MaxPooling is in charge of reducing computational overhead.
  Number of filters per kernel TBD. Activation is Leaky ReLU.
    > Kernel.shape(A, 1, B) <-- A being kernel height; B being channels
  - MaxPooling1D size 2 to reduce computational overhead by half per conv layer
  - BatchNorm applied channel-wise to reduce chance of overfitting
DECODER:
  - Upsample naively by 2, essentially opposite of MaxPooling1D; done by
  repeating every entry twice in the output.
  - Convolve using similar kernel to the encoder's, maintaining downward slope
  in overall size of nodes per layer.
  - Normalize channel-wise.
---------
Math
T = number of nodes in layer (T0 = 2880, T1 = 1440 due to Pooling)
t = timestep; how much time do we move between each group of samples.
  clarification: 2880 samples on first pass, move sample stack by 10 to move
  50 seconds into the past/future; t here is 10
E^ = activated output from convolving; standard activation taking weights,
  output from previous activation, biases (Leaky ReLU)
Batch normalization performed over the whole layer with the same m.
  formula: E = 1/(mAx+eP) * E^
  mAx = highest value in E^ including channels
  ePsilon = 10e-5; (batch norm)
  where max is taken along the last axis (filters/channels)
"""
model = keras.Sequential()

class MaxNormalization(Layer):

  def __init__(self, output_dim, **kwargs):
    self.output_dim = output_dim
    self.epsilon = 10e-5
    super(MaxNormalization, self).__init__(**kwargs)

  def build(self, input_shape):
    super(MaxNormalization, self).build(input_shape)

  def call(self, x):
    return 1/(np.amax(x) + epsilon) * x


DATA_SHAPE = (2880, 1)
RELU_SLOPE = 0.01       # Hyperparameter
CONV_FILTER_STEP = 32   # Grows constantly
CONV_KERNEL_SIZE = 2    # Small to keep high resolution, reduce for lower power
MAX_POOL_SIZE = 2       # Pool over 2 samples
HIDDEN_UNITS = 128      # Constant factor for hidden units in layer l
DNNl1 = 1               # Multiplier for hidden units in deep layer 1
DNNl2 = 1               # Multiplier for hidden units in deep layer 2

# <structure>
#   <encoder>
X = Conv1D(
  CONV_FILTER_STEP * 1,
  CONV_KERNEL_SIZE,
  input_shape=DATA_SHAPE)(X_train)
X = Activation('relu', a=RELU_SLOPE)(X)
X = MaxNormalization()(X)
X = MaxPool1D(MAX_POOL_SIZE, strides=2)(X)
#   </encoder>
#   <decoder>
X = Upsampling1D(2)(X)
X = Conv1D(CONV_FILTER_STEP * 2, CONV_KERNEL_SIZE)(X)
X = Activation('relu', a=RELU_SLOPE)(X)
X = MaxNormalization()(X)
#   </decoder>
#   <dnn>
X = Flatten()(X)
X = Dense(HIDDEN_UNITS * DNNl1)(X)
X = Activation('relu', a=RELU_SLOPE)(X)
X = Dense(HIDDEN_UNITS * DNNl2)(X)
X = Activation('relu', a=RELU_SLOPE)(X)
X = Dense(1, activation='sigmoid')(X)
#   </dnn>
# </structure>
