#include "matrix.h"
#include "mlp.h"
#ifndef UBERMAN_MATH_TESTING_H_
#include "testing.h"
#endif

MLP * mlp_model(int layers, float learning_rate, int batch_size);
HiddenLayer * hidden_layer(int units, int features, Activation activation);

void mlp_forward(Matrix * X, MLP * model);

void mlp_backward(Matrix * Y, Matrix * X, MLP * model);
static Matrix * compute_dAL(Matrix * Y, Matrix * A);
static Matrix * sigmoid_dZ(Matrix * dA, Matrix * A);
static Matrix * relu_dZ(Matrix * dA, Matrix * Z, float alpha);
static Matrix * compute_dW(Matrix * dZ, Matrix * A);
static Matrix * compute_db(Matrix * dZ);
static Matrix * compute_dA(Matrix * W, Matrix * dZ);

void update_params(MLP * model);
static void update_W(HiddenLayer * layer, float learning_rate);
static void update_b(HiddenLayer * layer, float learning_rate);

MLP * mlp_model(int layers, float learning_rate, int batch_size) {
  MLP * model = malloc(sizeof(MLP));

  model->layers = layers;
  model->learning_rate = learning_rate;
  model->batch_size = batch_size;

  model->_layers = malloc(layers * sizeof(*model->_layers));

  return model;
}

HiddenLayer * hidden_layer(int units, int features, Activation activation) {
  HiddenLayer * hidden_layer = malloc(sizeof(HiddenLayer));

  hidden_layer->units = units;
  hidden_layer->features = features;

  hidden_layer->W = matrix(units, features);
  hidden_layer->b = matrix(units, 1);
  hidden_layer->activation = activation;

  init_matrix_random(hidden_layer->W);
  init_matrix(hidden_layer->b, 0.0);

  return hidden_layer;
}


void mlp_forward(Matrix * X, MLP * model) {
  for (int i = 0; i < model->layers; i ++) {
    HiddenLayer * layer = model->_layers[i];
    
    if (i != 0) X = model->_layers[i-1]->A;

    // (units, features) x (features, examples) = (units, examples)
    Matrix * Z = product(layer->W, X);

    bump_vector(Z, layer->b);

    layer->Z = Z;

    Matrix * A = copy_matrix(Z);

    switch (layer->activation) {
      case RELU:
        relu(A, layer->params[relu_alpha]);
        break;
      case SIGMOID:
        sigmoid(A);
        break;
      default:
        break;
    }

    layer->A = A;

  }
}

static HiddenLayer * input_layer(Matrix * X) {
  HiddenLayer * input_layer = malloc(sizeof(HiddenLayer));
  input_layer->A = X;

  return input_layer;
}

void mlp_backward(Matrix * Y, Matrix * X, MLP * model) {
  Matrix * dA;

  for (int i = model->layers-1; i >= 0; i --) {
    HiddenLayer * layer = model->_layers[i];
    HiddenLayer * prev_layer = i == 0 ? input_layer(X) : model->_layers[i-1];

    if (i == model->layers-1) dA = compute_dAL(Y, layer->A);

    Matrix * dZ = layer->activation == RELU ?
      relu_dZ(dA, layer->Z, layer->params[relu_alpha]) :
      sigmoid_dZ(dA, layer->A);


    layer->db = compute_db(dZ);
    layer->dW = compute_dW(dZ, prev_layer->A);


    if (i != 1) dA = compute_dA(layer->W, dZ);
    clear(dZ);
  }
}

static Matrix * compute_dAL(Matrix * Y, Matrix * A) {
  Matrix * dAL = matrix(Y->n, Y->m);

  for (int i = 0; i < Y->m; i ++) {
    float y = Y->d[0][i];
    float a = A->d[0][i];

    dAL->d[0][i] = - ((y / a) - ((1 - y) / (1 - a)));
  }

  return dAL;
}

static Matrix * sigmoid_dZ(Matrix * dA, Matrix * A) {
  //dZ = dA ∗ A⋅(1−A)
  Matrix * dZ = matrix(A->n, A->m);

  for (int i = 0; i < A->m; i ++) {
    float da = dA->d[0][i];
    float a = A->d[0][i];

    dZ->d[0][i] = da * (a * (1 - a));
  }

  return dZ;
}

static Matrix * relu_dZ(Matrix * dA, Matrix * Z, float alpha) {
  Matrix * dZ = matrix(Z->n, Z->m);

  //dZ = dA ∗ g′(Z)

  for (int i = 0; i < Z->m; Z ++) {
    float da = dA->d[0][i];
    float z = Z->d[0][i];

    dZ->d[0][1] = da * (z > 0 ? 1 : alpha);
  }

  return dZ;
}

static Matrix * compute_dW(Matrix * dZ, Matrix * A) {
  Matrix * AT = transpose(A);
  Matrix * dW = product(dZ, AT);

  frac(dW, dZ->m);

  clear(AT);
  return dW;
}

static Matrix * compute_db(Matrix * dZ) {
  Matrix * sum = matrix_sum(dZ);

  frac(sum, dZ->m);

  return sum;
}

static Matrix * compute_dA(Matrix * W, Matrix * dZ) {
  Matrix * WT = transpose(W);
  Matrix * dA = product(WT, dZ);

  clear(WT);

  return dA;
}


void update_params(MLP * model) {
  float learning_rate = model->learning_rate;

  for (int i = 0; i < model->layers; i ++) {
    HiddenLayer * layer = model->_layers[i];
    printf("Layer: %d\n", i + 1);
    print_matrix(layer->W, "W update: \n");
    print_matrix(layer->dW, "dW update: \n");


    update_W(layer, learning_rate);
    update_b(layer, learning_rate);

  }
}
static void update_W(HiddenLayer * layer, float learning_rate) {
  for (int j = 0; j < layer->W->n; j ++)
    for (int k = 0; k < layer->W->m; k ++) {
        layer->W->d[j][k] -= layer->dW->d[j][k] * learning_rate;   
    }
}

static void update_b(HiddenLayer * layer, float learning_rate) {
  for (int j = 0; j < layer->b->n; j ++)
    for (int k = 0; k < layer->b->m; k ++)
      layer->b->d[j][k] -= layer->db->d[j][k] * learning_rate;
}

