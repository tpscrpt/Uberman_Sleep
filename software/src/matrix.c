#include "matrix.h"

void sigmoid(int n, int m, float ** X) {
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      X[i][j] = 1 / (1 + exp(-X[i][j]));
}

void bump(int n, int m, float ** X, float b) {
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      X[i][j] += b;
}


/* <https://github.com/gregdhill/lin-reg/blob/master/lreg.c> */

float** matrix(int n, int m) {
  float **X;
  X = (float **) malloc(n * sizeof (*X));

  for (int i=0; i<n; i++)
    X[i] = (float *) malloc(m * sizeof(*X[i]));

  return X;
}

void clear(int n, float** X){
  for (int i=0; i<n; i++)
    free(X[i]);
  free(X);
}

float** transpose(int n, int m, float** X) {
  float** X_ = matrix(m,n);

  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      X_[i][j] = X[j][i];

  return X_;
}

float** product(int n, int m, int p, int q, float** A, float** B) {
  float** C = matrix(n,q);

  for (int i = 0; i < n; i++)
    for (int j = 0; j < q; j++)
      C[i][j] = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < q; j++) {
      for (int k = 0; k < p; k++) {
        C[i][j] += A[i][k]*B[k][j];
      }
    }
  }

  return C;
}

/* </https://github.com/gregdhill/lin-reg/blob/master/lreg.c> */
