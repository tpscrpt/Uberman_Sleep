#include "matrix.h"
#include <stdarg.h>

#define NULL_PTR (void *)(0)

typedef void (*op_t)(float *, float[]);

// Generic loop over all of the elements in X, applying
// op_t to each of them and passing hyperparameters
static void inplace_op(Matrix * X, op_t op, float params[]) {
  for (int i = 0; i < X->n; i ++)
    for (int j = 0; j < X->m; j ++)
       op(&X->d[i][j], params);
}

// E.g.: each element is passed through *val, no params
// are used for the sigmoid function
static void sigmoid_op(float *val, float params[]) {
  *val = 1 / (1 + exp(-(*val)));
}
// Helper function, could be omitted for less succinct
// source code
void sigmoid(Matrix * X) {
  inplace_op(X, &sigmoid_op, NULL_PTR);
}

// Similar to sigmoid_op, but this time a param is used
// as a coefficient on val if it's negative
static void relu_op(float *val, float params[]) {
  *val = *val > 0 ? *val : *val * params[0];
}
// Helper function which would also be unintuitive
// Note: for ReLU pass 0 as "a", Leaky pass anything
void relu(Matrix * X, float a) {
  float params[1] = { a };
  inplace_op(X, &relu_op, params);
}

static void bump_op(float *val, float params[]) {
  *val = *val + params[0];
}
void bump(Matrix * X, float b) {
  float params[1] = { b };
  inplace_op(X, &bump_op, params);
}

Matrix * matrix(int n, int m) {
  Matrix * mat = malloc(sizeof(struct Matrix));
  mat->n = n;
  mat->m = m;

  mat->d = malloc(n * sizeof (*mat->d));

  for (int i = 0; i < n; i++)
    mat->d[i] = malloc(m * sizeof(*mat->d[i]));

  return mat;
}

void clear(Matrix * X) {
  for (int i = 0; i < X->n; i ++)
    free(X->d[i]);
  
  free(X->d);
}

void init_op(float * val, float params[]) {
  *val = params[0];
}
void init_matrix(Matrix * X, float val) {
  float params[1] = { val };
  inplace_op(X, &init_op, params);
}


Matrix * transpose(Matrix * X) {
  Matrix * X_ = matrix(X->m, X->n);

  for (int i = 0; i < X->m; i++)
    for (int j = 0; j < X->n; j++)
      X_->d[i][j] = X->d[j][i];

  return X_;
}

Matrix * product(Matrix * A, Matrix * B) {
  int n = A->n;
  int m = A->m;
  int p = B->n;
  int q = B->m;

  Matrix * C = matrix(n, q);

  for (int i = 0; i < n; i++)
    for (int j = 0; j < q; j++)
      C->d[i][j] = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < q; j++) {
      for (int k = 0; k < p; k++) {
        C->d[i][j] += A->d[i][k] * B->d[k][j];
      }
    }
  }

  return C;
}

/* </https://github.com/gregdhill/lin-reg/blob/master/lreg.c> */
