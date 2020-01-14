#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

void sigmoid(Matrix * X) {
  for (int i = 0; i < X->n; i ++)
    for (int j = 0; j < X->m; j ++)
      X->d[i][j] = 1 / (1 + exp(-X->d[i][j]));
}

void relu(Matrix * X, float a) {
  for (int i = 0; i < X->n; i ++)
    for (int j = 0; j < X->m; j ++)
      X->d[i][j] = X->d[i][j] > 0 ? X->d[i][j] : a * X->d[i][j];
}

void bump(Matrix * X, float b) {
  for (int i = 0; i < X->n; i ++)
    for (int j = 0; j < X->m; j ++)
      X->d[i][j] += b;
}

void bump_column(Matrix * X, Matrix * b) {
    for (int i = 0; i < X->n; i ++)
        for (int j = 0; j < X->m; j ++)
            X->d[i][j] += b->d[i][0];
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

void init_matrix(Matrix * X, float val) {
  for (int i = 0; i < X->n; i ++)
    for (int j = 0; j < X->m; j ++)
        X->d[i][j] = val;
}
void init_matrix_random(Matrix * X) {
  for (int i = 0; i < X->n; i ++)
    for (int j = 0; j < X->m; j ++)
      X->d[i][j] = (float) drand48();
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

Matrix * matrix_copy(Matrix * X) {
  Matrix * X_ = matrix(X->n, X->m);

  for (int i = 0; i < X->n; i++)
    for (int j = 0; j < X->m; j++)
      X_->d[i][j] = X->d[i][j];

  return X_;
}

void print_matrix(Matrix * X, char* msg) {
  printf("%s", msg);
  printf("(%d, %d)\n", X->n, X->m);

  for (int i = 0; i < X->n; i ++) {
    for (int j = 0; j < X->m; j ++)
      printf("%f ", X->d[i][j]);

    printf("\n");
  }
}
/* </https://github.com/gregdhill/lin-reg/blob/master/lreg.c> */
