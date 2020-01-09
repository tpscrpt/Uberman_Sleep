#include "matrix.h"
#include "logreg.h"

#include <stdio.h>

void logreg(
  Matrix * X,   // data
  Matrix * Y,   // labels
  Matrix * W,   // weights
  float  * b,   // intercept
  int      m,   // examples
  int      nx,  // features
  float    a    // learning rate
) {
  // compute predictions
  Matrix * A = forward_pass(X, W, *b);

  // compute derivatives for gradient descent
  float cost = compute_cost(A, Y);
  Matrix * dZ = compute_dZ(A, Y);
  Matrix * dW = compute_dW(X, dZ);
  float db = compute_db(dZ);

  // update parameters
  update_W(W, dW, a);
  update_b(b, db, a);

  clear(A);
  clear(dZ);
  clear(dW);
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