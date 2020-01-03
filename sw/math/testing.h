#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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

void print_matrix(int n, int m, float** matrix) {
  for (int i = 0; i < n; i ++) {
    for (int j = 0; j < m; j ++)
      printf("%f ", matrix[i][j]);

    printf("\n");
  }

  printf("\n");
}