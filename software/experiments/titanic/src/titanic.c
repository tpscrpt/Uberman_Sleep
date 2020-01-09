#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "csv.h"
#include "matrix.h"
#include "testing.h"

static int ** alloc_mati(int m, int n);
static float ** alloc_matf(int m, int n);

void cleari(int n, int** X);
void clearf(int n, float** X);

float compute_cost(int n, int m, float ** X, float ** Y);
float ** compute_da(int n, int m, float ** X, float ** Y);
float ** compute_dZ(int n, int m, float ** X, float ** Y);
float ** compute_dW(float ** X, int n, int m, float ** dZ, int p, int q);
float compute_db(int n, int m, float ** dZ);

void update_W(float ** W, float ** dW, int m, float learning_rate);
void update_b(float * b, float db, float learning_rate);

int main () {
  int testing = 1;
  // Source file for training data
  FILE * train = fopen("experiments/titanic/output/train_cleaned.csv", "r");

  // Check whether we have data in the file
  if (csvgetline(train) == NULL) {
    return printf("Exiting due to bad file");
  }

  // looping variables
  int i, j, e;

  // constants for the logistic regression
  int batch_size = 10;
  double learning_rate = 0.1;
  int epochs = 800;

  // number of features for each example
  int features = csvnfield() - 1;

  // total number of examples in the training set
  int examples = 714;
  // ratio of training examples allocated to the train set
  float ratio = 0.8;

  // number of examples to be allocated to the *train* set
  int train_examples = examples * ratio;
  // number of examples to be allocated to the *dev* set
  int dev_examples = examples * (1 - ratio);

  // make sure we are allocating all of our examples
  if (dev_examples + train_examples < examples)
    train_examples++;

  // initialize train matrices (X = features, Y = label)
  float ** train_X = alloc_matf(features, train_examples);
  float ** train_Y = alloc_matf(1, train_examples);

  // initialize dev matrices (X = features, Y = label)
  float ** dev_X = alloc_matf(features, dev_examples);
  float ** dev_Y = alloc_matf(1, dev_examples);   

  // initialize weight matrix (transposed)
  float ** W = alloc_matf(1, features);
    init_matrix_val(1, features, W, 0.5);

  // initialize bias scalar
  float b = 0.0;

  for (i = 0; csvgetline(train) != NULL && i < examples; i ++) {
    int update_dev = i >= train_examples;               // start placing examples in dev_X and dev_Y
    int index = update_dev ? i - train_examples : i;    // shift down index when targeting dev set

    float ** update_X = update_dev ? dev_X : train_X;   // set example matrix to append to as train or dev
    float ** update_Y = update_dev ? dev_Y : train_Y;   // set label matrix to append to as train or dev

    int survived = atoi(csvfield(0));                   // whether the label is 0 or 1 (dead or survived)
    update_Y[0][index] = survived ? 1 : 0;              // set the label value for the given example


    for (j = 0; j < features; j ++) {
      update_X[j][index] = atof(csvfield(j+1));           // set each feature value for the given example
    }
  }

  //print_matrix(features, train_examples, train_X, "Train X: \n");

  for(e = 0; e < epochs; e ++) {
    //if (e == 0) print_matrix(features, train_examples, train_X, "Train_X: \n");
    float ** WX = product(1, features, features, train_examples, W, train_X);
    //print_matrix(1, train_examples, WX, "wX: \n");

    bump(1, train_examples, WX, b);
    //print_matrix(1, train_examples, WX, "Z: \n");

    sigmoid(1, train_examples, WX);
    //print_matrix(1, train_examples, WX, "A: \n");

    float cost = compute_cost(1, train_examples, WX, train_Y);
    float ** da = compute_da(1, train_examples, WX, train_Y);
    float ** dZ = compute_dZ(1, train_examples, WX, train_Y);
    float ** dW = compute_dW(train_X, features, train_examples, dZ, 1, train_examples);
    float db = compute_db(1, train_examples, dZ);

    print_matrix(1, features, W, "\nW pre-update: \n");
    update_W(W, dW, features, learning_rate);
    print_matrix(1, features, W, "\nW post-update: \n");

    printf("b pre-update: %f\n", b);
    update_b(&b, db, learning_rate);
    printf("b post-update: %f\n", b);
  }

  // w.shape = (1, features)
  // x.shape = (features, examples)
  // wx = (1, examples)

  clearf(features, train_X);
  clearf(1, train_Y);
  clearf(features, dev_X);
  clearf(1, dev_Y);
}

void update_W(float ** W, float ** dW, int m, float learning_rate) {
  for (int i = 0; i < m; i ++)
    W[0][i] -= (learning_rate * dW[0][i]);
}

void update_b(float * b, float db, float learning_rate) {
  *b -= (learning_rate * db);
}

float compute_db(int n, int m, float ** dZ) {
  float sum = 0.0;

  for (int i = 0; i < m; i ++)
    sum += dZ[0][i];

  return sum / (float) m;
}

float ** compute_dW(float ** X, int n, int m, float ** dZ, int p, int q) {
  // X = (features, train_examples)
  // dZ = (1, train_examples)
  // dZT = (train_examples, 1)
  // dW = (features, 1)
  // dWT = (1, features) -- same shape as transposed W

  float ** dZT = transpose(p, q, dZ);
  float ** dW = product(n, m, q, p, X, dZT);
  float ** dWT = transpose(n, p, dW);

  for (int i = 0; i < n; i ++)
    dWT[0][i] /= (float) m;

  return dWT;  
}

float ** compute_dZ(int n, int m, float ** X, float ** Y) {
  float ** dZ = alloc_matf(n, m);
  
  for (int i = 0; i < m; i ++) {
    float y = Y[0][i];
    float a = X[0][i];

    dZ[0][i] = (float) a - y;
  }

  return dZ;
}

float ** compute_da(int n, int m, float ** X, float ** Y) {
  float ** da = alloc_matf(n, m);
  
  for (int i = 0; i < m; i ++) {
    float y = Y[0][i];
    float a = X[0][i];

    da[0][i] = (float) (-y / a) + ((1 - y) / (1 - a));
  }

  return da;
}

float compute_cost(int n, int m, float ** X, float ** Y) {
  float sum = 0.0;

  for (int i = 0; i < m; i ++) {
    float y = Y[0][i];
    float y_hat = X[0][i];

    sum += (float) y * logf(y_hat) + ((1 - y) * logf(1 - y_hat));
  }

  return - (sum / (float) m);
}

static int ** alloc_mati(int n, int m) {
  int **X;
  X = (int **) malloc(n * sizeof (*X));

  for (int i=0; i<n; i++)
    X[i] = (int *) malloc(m * sizeof(*X[i]));

  return X;
}
static float ** alloc_matf(int n, int m) {
  float **X;
  X = (float **) malloc(n * sizeof (*X));

  for (int i=0; i<n; i++)
    X[i] = (float *) malloc(m * sizeof(*X[i]));

  return X;
}

void cleari(int n, int** X){
  for (int i=0; i<n; i++)
    free(X[i]);
  free(X);
}
void clearf(int n, float** X){
  for (int i=0; i<n; i++)
    free(X[i]);
  free(X);
}