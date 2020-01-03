#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

double fast_sigmoid(float z) {
  return z / (1 + abs(z));
}

void sigmoid(int n, int m, float ** X) {
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      X[i][j] = 1 / (1 + exp(-X[i][j]));
}

void bump(int n, int m, float ** X, float c) {
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      X[i][j] += c;
}

float average(int n, int m, float ** X) {
  float avg = 0;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      avg += X[i][j];

  if (avg == 0) return 0;

  return avg / (n * m);
}

/* <https://github.com/gregdhill/lin-reg/blob/master/lreg.c> */
void clear(int n, float** X){
  for (int i=0; i<n; i++)
    free(X[i]);
  free(X);
}

float** matrix(int n, int m) {
  float **X;
  X = (float **) malloc(n * sizeof (*X));

  for (int i=0; i<n; i++)
    X[i] = (float *) malloc(m * sizeof(*X[i]));

  return X;
}

// Changes shape of matrix, therefore clear() old matrix
float** transpose(int n, int m, float** X) {
  float** X_ = matrix(m,n);

  for (size_t i = 0; i < m; i++)
    for (size_t j = 0; j < n; j++)
      X_[i][j] = X[j][i];

  return X_;
}

// Changes shape of matrix, therefore clear() old matrixes
float** product(int n, int m, int p, int q, float** A, float** B) {
  float** C = matrix(n,q);

  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < q; j++)
      C[i][j] = 0;

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < q; j++) {
      for (size_t k = 0; k < p; k++) {
        C[i][j] += A[i][k]*B[k][j];
      }
    }
  }

  return C;
}
/* </https://github.com/gregdhill/lin-reg/blob/master/lreg.c> */

