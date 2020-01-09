#include "matrix.h"

void sigmoid(Matrix * X) {
  for (int i = 0; i < X->n; i ++)
    for (int j = 0; j < X->m; j ++)
      X->d[i][j] = 1 / (1 + exp(-X->d[i][j]));
}

void bump(Matrix * X, float b) {
  for (int i = 0; i < X->n; i ++)
    for (int j = 0; j < X->m; j ++)
      X->d[i][j] += b;
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

void init_val(Matrix * X, float val) {
  for (int i = 0; i < X->n; i ++)
    for (int j = 0; j < X->m; j ++)
      X->d[i][j] = val;
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
