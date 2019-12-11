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
class TCN():
  def __init__(self,
               DATA_SHAPE = (2880, 1),
               RELU_SLOPE = 0.01,       # Hyperparameter
               CONV_FILTER_STEP = 32,   # Grows constantly
               CONV_KERNEL_SIZE = 2,    # Small to keep high resolution, reduce for lower power
               MAX_POOL_SIZE = 2,       # Pool over 2 samples
               HIDDEN_UNITS = 128,      # Constant factor for hidden units in layer l
               DNNl = [1, 1]):          # Nb of layers / Multiplier for hidden units layer

    self.RELU_SLOPE = RELU_SLOPE
    self.CONV_FILTER_STEP = CONV_FILTER_STEP
    self.CONV_KERNEL_SIZE = CONV_KERNEL_SIZE
    self.MAX_POOL_SIZE = MAX_POOL_SIZE
    self.HIDDEN_UNITS = HIDDEN_UNITS
    self.DNNl = DNNl

    self.model = keras.Sequential()
    self.callbacks = [
      keras.callbacks.ModelCheckpoint(
          filepath='models/best_model.{epoch:02d}-{val_loss:.2f}.h5',
          monitor='val_loss', save_best_only=True),
      keras.callbacks.EarlyStopping(monitor='acc', patience=0.98)
    ]

  def add_encoder(self, first=False, X_train=None):
    if first is True:
      self.X = Conv1D(
        self.CONV_FILTER_STEP * 1,
        self.CONV_KERNEL_SIZE,
        input_shape=self.DATA_SHAPE)(X_train)
    else:
      self.X = Conv1D(
        self.CONV_FILTER_STEP * 1,
        self.CONV_KERNEL_SIZE)(self.X)

    self.X = Activation('relu', a=self.RELU_SLOPE)(self.X)
    self.X = MaxNormalization()(self.X)
    self.X = MaxPool1D(self.MAX_POOL_SIZE, strides=2)(self.X)

  def add_decoder(self):
    self.X = Upsampling1D(2)(self.X)
    self.X = Conv1D(self.CONV_FILTER_STEP * 2, self.CONV_KERNEL_SIZE)(self.X)
    self.X = Activation('relu', a=self.RELU_SLOPE)(self.X)
    self.X = MaxNormalization()(self.X)

  def flatten(self):
    self.X = Flatten()(self.X)

  def dense(self):
    for layer in self.DNNl:
      self.X = Dense(self.HIDDEN_UNITS * layer, activation='relu', a=self.RELU_SLOPE)(self.X)

    self.X = Dense(1, activation='sigmoid')(self.X)

  def compile(self):
    self.model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])

  def fit(self, Y, batch_size=None, epochs=None):
    self.model.fit(self.X, Y,
                   epochs=epochs,
                   batch_size=batch_size,
                   callbacks=self.callbacks)

  def evaluate(self, X, Y):
    self.model.evaluate(X, Y)

class MaxNormalization(keras.layers.Layer):

  def __init__(self, output_dim, **kwargs):
    self.output_dim = output_dim
    self.epsilon = 10e-5
    super(MaxNormalization, self).__init__(**kwargs)

  def build(self, input_shape):
    super(MaxNormalization, self).build(input_shape)

  def call(self, x):
    return 1/(np.amax(x) + epsilon) * x
