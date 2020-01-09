#ifndef UBERMAN_MATH_TESTING_H_
#define UBERMAN_MATH_TESTING_H_

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"

void init_random_matrix(int n, int m, float** matrix) {
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      matrix[i][j] = (float)rand()/(float)(RAND_MAX);
}
void init_same_matrix(int n, int m, float** matrix, float val) {
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      matrix[i][j] = val;
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

#endif