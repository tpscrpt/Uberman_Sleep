#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "csv.h"
#include "matrix.h"
#include "testing.h"


Matrix * forward_pass(Matrix * X, Matrix * W, float b);
float compute_cost(Matrix * A, Matrix * Y);
Matrix * compute_dZ(Matrix * A, Matrix * Y);
Matrix * compute_dW(Matrix * X, Matrix * dZ);
float compute_db(Matrix * dZ);

void update_W(Matrix * W, Matrix * dW, float learning_rate);
void update_b(float * b, float db, float learning_rate);


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
  Matrix * train_X = matrix(features, train_examples);
  Matrix * train_Y = matrix(1, train_examples);
  Matrix * dev_X = matrix(features, dev_examples);
  Matrix * dev_Y = matrix(1, dev_examples);

  // initialize weight matrix (transposed, may be revised)
  Matrix * W = matrix(1, features);
    init_val(W, 0.0);

  // initialize bias scalar
  float b = 0.0;

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

  for(e = 0; e < epochs; e ++) {
    // compute predictions
    Matrix * train_A = forward_pass(train_X, W, b);

    // compute derivatives for gradient descent
    float cost = compute_cost(train_A, train_Y);
    Matrix * dZ = compute_dZ(train_A, train_Y);
    Matrix * dW = compute_dW(train_X, dZ);
    float db = compute_db(dZ);

    // update parameters
    update_W(W, dW, learning_rate);
    update_b(&b, db, learning_rate);

    clear(train_A);
    clear(dZ);
    clear(dW);
  }

  print_matrix(W, "\nW: ");
  printf("b: %f\n\n", b);

  clear(train_X);
  clear(train_Y);

  // ---- run predictions on dev set ----------------
  Matrix * dev_A = forward_pass(dev_X, W, b);
  float accurate = 0.0;

  for (i = 0; i < dev_examples; i ++)
    if (dev_A->d[0][i] > 0.5 && dev_Y->d[0][i] > 0.5 ||
        dev_A->d[0][i] <= 0.5 && dev_Y->d[0][i] < 0.5) accurate++;

  accurate /= (float) dev_examples;

  printf("Accuracy on dev set: %f\n\n", accurate);
  
  clear(dev_X);
  clear(dev_Y);
  clear(dev_A);


  // ---- run predictions on test set ----------------
  FILE * test = fopen("experiments/titanic/output/test_cleaned.csv", "r");
  FILE * submission = fopen("experiments/titanic/output/c_submission.csv", "w");

  // Check whether we have data in the file
  if (csvgetline(test) == NULL) {
    return printf("Exiting due to bad file");
  }

  int test_examples = 331;

  Matrix * test_X = matrix(features, test_examples);
  Matrix * test_Y = matrix(1, test_examples);

  for (i = 0; csvgetline(test) != NULL && i < test_examples; i ++) {
    test_Y->d[0][i] = atoi(csvfield(0));             // extract id of passenger

    for (j = 0; j < features; j ++)
      test_X->d[j][i] = atof(csvfield(j+1));         // set each feature value for the given example
  }

  fclose(test);

  // get prediction vector
  Matrix * test_A = forward_pass(test_X, W, b);

  // csv header
  fprintf(submission, "PassengerId,Survived\n");

  // output the passenger's ID and whether we think they survived
  for (i = 0; i < test_examples; i ++)
    fprintf(submission, "%d,%d\n", (int) test_Y->d[0][i], test_A->d[0][i] > 0.5);

  clear(test_X);
  clear(test_Y);
  clear(test_A);
  fclose(submission);
}

Matrix * forward_pass(Matrix * X, Matrix * W, float b) {
  Matrix * WX = product(W, X);
  bump(WX, b);
  sigmoid(WX);

  return WX;
}

float compute_cost(Matrix * A, Matrix * Y) {
  float sum = 0.0;

  for (int i = 0; i < A->m; i ++) {
    float y = Y->d[0][i];
    float a = A->d[0][i];

    sum += (float) y * logf(a) + ((1 - y) * logf(1 - a));
  }

  return - (sum / (float) A->m);
}

Matrix * compute_dZ(Matrix * A, Matrix * Y) {
  Matrix * dZ = matrix(A->n, A->m);

  for (int i = 0; i < A->m; i ++) {
    float y = Y->d[0][i];
    float a = A->d[0][i];

    dZ->d[0][i] = (float) a - y;
  }

  return dZ;
}

Matrix * compute_dW(Matrix * X, Matrix * dZ) {
  Matrix * dZT = transpose(dZ);

  Matrix * dW = product(X, dZT);
  clear(dZT);

  Matrix * dWT = transpose(dW);
  clear(dW);

  for (int i = 0; i < X->n; i ++)
    dWT->d[0][i] /= (float) X->m;

  return dWT;
}


float compute_db(Matrix * dZ) {
  float sum = 0.0;

  for (int i = 0; i < dZ->m; i ++)
    sum += dZ->d[0][i];

  return sum / (float) dZ->m;
}
void update_W(Matrix * W, Matrix * dW, float learning_rate) {
  for (int i = 0; i < W->m; i ++)
    W->d[0][i] -= (learning_rate * dW->d[0][i]);
}

void update_b(float * b, float db, float learning_rate) {
  *b -= (learning_rate * db);
}