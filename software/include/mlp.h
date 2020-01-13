#ifndef UBERMAN_MATH_MLP_H_
#define UBERMAN_MATH_MLP_H_

#include "matrix.h"

typedef enum Activation {
  RELU,
  SIGMOID
} Activation;

typedef enum RELU_Params {
  relu_alpha
} RELU_Params;

typedef struct HiddenLayer {
  int units;              // number of nodes in layer
  int features;           // number of input features
  Matrix * W;             // (units, features)
  Matrix * b;             // (units, 1)
  Matrix * Z;             // (units, examples)
  Matrix * A;             // (units, examples)
  Matrix * dA;            // (units, examples)
  Matrix * db;            // (units, 1)
  Matrix * dW;            // (units, features)
  Activation activation;  // name of the activation function
  float params[];         // parameters to pass to the activation function
} HiddenLayer;

typedef struct MLP {
  int layers;
  HiddenLayer ** _layers;
  float learning_rate;
  int batch_size;
} MLP;

extern MLP * mlp_model(int layers, float learning_rate, int batch_size);
extern HiddenLayer * hidden_layer(int units, int features, Activation activation);
extern void mlp_forward(Matrix * X, MLP * model);
extern void mlp_backward(Matrix * Y, Matrix * X, MLP * model);
extern void update_params(MLP * model);

#endif