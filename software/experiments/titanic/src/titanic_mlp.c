#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "csv.h"
#include "matrix.h"
//#include "testing.h"
#include "mlp.h"

int main () {
  // Source file for training data
  FILE * train = fopen("experiments/titanic/output/train_cleaned.csv", "r");

  // Check whether we have data in the file
  if (csvgetline(train) == NULL) {
    return printf("Exiting due to bad file");
  }

  int i, j, e;

  // constants for the ML
  float learning_rate = 0.1;
  int batch_size = 10;
  int epochs = 800;

  // number of features for each example
  int features = csvnfield() - 1;

  // total number of examples in the training set
  int examples = 10;
  // ratio of training examples allocated to the train set
  float ratio = 0.8;

  int train_examples = examples * ratio;
  int dev_examples = examples * (1 - ratio);

  // make sure we are allocating all of our examples
  if (dev_examples + train_examples < examples)
    train_examples++;

  // initialize train and dev matrices (X = features, Y = label)
  Matrix * train_X = matrix(features, train_examples);
  Matrix * train_Y = matrix(1, train_examples);
  Matrix * dev_X = matrix(features, dev_examples);
  Matrix * dev_Y = matrix(1, dev_examples);

  MLP * model = mlp_model(2, learning_rate, batch_size);

  HiddenLayer * layer_1 = hidden_layer(10, features, RELU);
  HiddenLayer * layer_2 = hidden_layer(1, 10, SIGMOID);

  model->_layers[0] = layer_1;
  model->_layers[1] = layer_2;

  for (i = 0; csvgetline(train) != NULL && i < examples; i ++) {
    int update_dev = i >= train_examples;               // start placing examples in dev_X and dev_Y
    int index = update_dev ? i - train_examples : i;    // shift down index when targeting dev set

    Matrix * update_X = update_dev ? dev_X : train_X;   // set example matrix to append to as train or dev
    Matrix * update_Y = update_dev ? dev_Y : train_Y;   // set label matrix to append to as train or dev

    int survived = atoi(csvfield(0));                   // whether the label is 0 or 1 (dead or survived)
    update_Y->d[0][index] = survived ? 1 : 0;           // set the label value for the given example

    for (j = 0; j < features; j ++) {
      update_X->d[j][index] = atof(csvfield(j+1));      // set each feature value for the given example
    }
  }

  fclose(train);

  // (features, examples)
  mlp_forward(train_X, model);

  //print_matrix(model->_layers[0]->W, "\nW1: \n");
  //print_matrix(model->_layers[0]->A, "\nA1: \n");
  //print_matrix(model->_layers[1]->W, "\nW2: \n");
  //print_matrix(model->_layers[1]->A, "\nA2: \n");

  mlp_backward(train_Y, train_X, model);

  //print_matrix(model->_layers[0]->dW, "\ndW1: \n");
  //print_matrix(model->_layers[0]->db, "\ndb1: \n");
  //print_matrix(model->_layers[1]->dW, "\ndW2: \n");
  //print_matrix(model->_layers[1]->db, "\ndb2: \n");

  update_params(model);

  //print_matrix(model->_layers[0]->W, "\nW1: \n");
  //print_matrix(model->_layers[0]->b, "\nb1: \n");
  //print_matrix(model->_layers[1]->W, "\nW2: \n");
  //print_matrix(model->_layers[1]->b, "\nb2: \n");

  for(e = 0; e < epochs; e ++) {
    
  }
}