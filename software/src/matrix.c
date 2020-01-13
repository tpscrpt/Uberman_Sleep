#include "matrix.h"
#include <stdlib.h>

#define NULL_PTR (void *)(0)

typedef void (*op_t)(float *, float[]);

/* Generic loop over all of the elements in X, applying
 * op_t to each of them and passing hyperparameters
 */
static void inplace_op(Matrix * X, op_t op, float params[]) {
  for (int i = 0; i < X->n; i ++)
    for (int j = 0; j < X->m; j ++)
       op(&X->d[i][j], params);
}


/* Apply the sigmoid function to every element of a matrix */
static void sigmoid_op(float *val, float params[]) {
  *val = 1 / (1 + exp(-(*val)));
}
void sigmoid(Matrix * X) {
  inplace_op(X, &sigmoid_op, NULL_PTR);
}

/* Perform ReLU on every element of a matrix,
 * multiplying them by "a" if negative
 * use a != 0.0 for Leaky ReLU 
 */
static void relu_op(float *val, float params[]) {
  *val = *val > 0 ? *val : *val * params[0];
}
void relu(Matrix * X, float a) {
  float params[1] = { a };
  inplace_op(X, &relu_op, params);
}

/* Vector addition */
void bump_vector(Matrix * X, Matrix * b) {
  for (int i = 0; i < X->n; i ++)
    X->d[i][0] += b->d[i][0];
}

/* Add a scalar value to all elements of a matrix */
static void bump_op(float *val, float params[]) {
  *val = *val + params[0];
}
void bump(Matrix * X, float b) {
  float params[1] = { b };
  inplace_op(X, &bump_op, params);
}

/* Divide every element of a matrix by a scalar */
static void frac_op(float *val, float params[]) {
  *val /= params[0];
}
void frac(Matrix * X, float m) {
  float params[1] = { m };
  inplace_op(X, &frac_op, params);
}

/* Initialize elements of a matrix to the same value */
static void init_op(float * val, float params[]) {
  *val = params[0];
}
void init_matrix(Matrix * X, float val) {
  float params[1] = { val };
  inplace_op(X, &init_op, params);
}


/* Initialize elements of a matrix to random values */
static void init_op_random(float * val, float params[]) {
  *val = (float)rand()/(float)(RAND_MAX);
}
void init_matrix_random(Matrix * X) {
  inplace_op(X, &init_op_random, NULL_PTR);
}


Matrix * copy_matrix(Matrix * X) {
  Matrix * X_ = matrix(X->n, X->m);

  for (int i = 0; i < X->n; i ++)
    for (int j = 0; j < X->m; j ++)
      X_->d[i][j] = X->d[i][j];

  return X_;
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

Matrix * matrix_sum(Matrix * X) {
  Matrix * sum = matrix(X->n, 1);

  for (int i = 0; i < X->n; i ++) {
    sum->d[i][0] = 0.0;
    for (int j = 0; j < X->m; j ++)
      sum->d[i][0] += X->d[i][j]; 
  }

  return sum;
}

// Constructor
Matrix * matrix(int n, int m) {
  Matrix * mat = malloc(sizeof(Matrix));
  mat->n = n;
  mat->m = m;

  mat->d = malloc(n * sizeof (*mat->d));

  for (int i = 0; i < n; i++)
    mat->d[i] = malloc(m * sizeof(*mat->d[i]));

  return mat;
}

// Destructor
void clear(Matrix * X) {
  for (int i = 0; i < X->n; i ++)
    free(X->d[i]);
  
  free(X->d);
}
