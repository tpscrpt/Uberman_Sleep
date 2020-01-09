#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "csv.h"
#include "matrix.h"
#include "testing.h"

float compute_cost(int n, int m, float ** X, float ** Y);
float ** compute_dZ(int n, int m, float ** X, float ** Y);
float ** compute_dW(float ** X, int n, int m, float ** dZ, int p, int q);
float compute_db(int n, int m, float ** dZ);

void update_W(float ** W, float ** dW, int m, float learning_rate);
void update_b(float * b, float db, float learning_rate);

float ** forward_pass(float ** X, int features, int examples, float ** W, float b);

/*
    NOTE: I keep my W vectors transposed at all times in main
    because it feels like it may use less memory overall.
    This is subject to change!
*/

int main () {
  // Source file for training data
  FILE * train = fopen("experiments/titanic/output/train_cleaned.csv", "r");

  // Check whether we have data in the file
  if (csvgetline(train) == NULL) {
    return printf("Exiting due to bad file");
  }

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

  int train_examples = examples * ratio;
  int dev_examples = examples * (1 - ratio);

  // make sure we are allocating all of our examples
  if (dev_examples + train_examples < examples)
    train_examples++;

  // initialize train and dev matrices (X = features, Y = label)
  float ** train_X = matrix(features, train_examples);
  float ** train_Y = matrix(1, train_examples);
  float ** dev_X = matrix(features, dev_examples);
  float ** dev_Y = matrix(1, dev_examples);   

  // initialize weight matrix (transposed, may be revised)
  float ** W = matrix(1, features);
    init_matrix_val(1, features, W, 0.0);

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
      update_X[j][index] = atof(csvfield(j+1));         // set each feature value for the given example
    }
  }

  fclose(train);

  for(e = 0; e < epochs; e ++) {
    // compute predictions
    float ** train_A = forward_pass(train_X, features, train_examples, W, b);

    // compute derivatives for gradient descent
    float cost = compute_cost(1, train_examples, train_A, train_Y);
    float ** dZ = compute_dZ(1, train_examples, train_A, train_Y);
    float ** dW = compute_dW(train_X, features, train_examples, dZ, 1, train_examples);
    float db = compute_db(1, train_examples, dZ);

    // update parameters
    update_W(W, dW, features, learning_rate);
    update_b(&b, db, learning_rate);

    clear(1, train_A);
    clear(1, dZ);
    clear(1, dW);
  }

  print_matrix(1, features, W, "\nW: ");
  printf("b: %f\n\n", b);

  clear(features, train_X);
  clear(1, train_Y);

  // ---- run predictions on dev set ----------------
  float ** dev_A = forward_pass(dev_X, features, dev_examples, W, b);
  float accurate = 0.0;

  for (i = 0; i < dev_examples; i ++)
    if (dev_A[0][i] > 0.5 && dev_Y[0][i] > 0.5 ||
        dev_A[0][i] <= 0.5 && dev_Y[0][i] < 0.5) accurate++;

  accurate /= (float) dev_examples;

  printf("Accuracy on dev set: %f\n\n", accurate);
  
  clear(features, dev_X);
  clear(1, dev_Y);
  clear(1, dev_A);


  // ---- run predictions on test set ----------------
  FILE * test = fopen("experiments/titanic/output/test_cleaned.csv", "r");
  FILE * submission = fopen("experiments/titanic/output/c_submission.csv", "w");

  // Check whether we have data in the file
  if (csvgetline(test) == NULL) {
    return printf("Exiting due to bad file");
  }

  int test_examples = 331;

  float ** test_X = matrix(features, test_examples);
  float ** test_Y = matrix(1, test_examples);

  for (i = 0; csvgetline(test) != NULL && i < test_examples; i ++) {
    test_Y[0][i] = atoi(csvfield(0));             // extract id of passenger

    for (j = 0; j < features; j ++)
      test_X[j][i] = atof(csvfield(j+1));         // set each feature value for the given example
  }

  fclose(test);

  float ** test_A = forward_pass(test_X, features, test_examples, W, b);

  fprintf(submission, "PassengerId,Survived\n");

  for (i = 0; i < test_examples; i ++)
    fprintf(submission, "%d,%d\n", (int) test_Y[0][i], test_A[0][i] > 0.5);

  clear(features, test_X);
  clear(1, test_Y);
  clear(1, test_A);
  fclose(submission);
}

float ** forward_pass(float ** X, int features, int examples, float ** W, float b) {
  // multiply input features by coefficients across all examples
  float ** WX = product(1, features, features, examples, W, X);

  bump(1, examples, WX, b);   // add bias to create the Z vector
  sigmoid(1, examples, WX);   // element-wise sigmoid yields A vector (predictions)

  return WX;
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

float ** compute_dZ(int n, int m, float ** X, float ** Y) {
  float ** dZ = matrix(n, m);
  
  for (int i = 0; i < m; i ++) {
    float y = Y[0][i];
    float a = X[0][i];

    dZ[0][i] = (float) a - y;
  }

  return dZ;
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

float compute_db(int n, int m, float ** dZ) {
  float sum = 0.0;

  for (int i = 0; i < m; i ++)
    sum += dZ[0][i];

  return sum / (float) m;
}

void update_W(float ** W, float ** dW, int m, float learning_rate) {
  for (int i = 0; i < m; i ++)
    W[0][i] -= (learning_rate * dW[0][i]);
}

void update_b(float * b, float db, float learning_rate) {
  *b -= (learning_rate * db);
}