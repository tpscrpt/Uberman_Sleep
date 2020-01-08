#include <stdio.h>
#include <stdlib.h>
#include "../math/functions.h"
#include "./_math.h"


int main() {
  int n = 5;
  int m = 3;

   // <transpose()>
  print_section("transpose");

  float** testMatrix = matrix(n, m);
  init_random_matrix(n, m, testMatrix);
  print_matrix(n, m, testMatrix);
  clear(n, testMatrix);

  float** testMatrix_t = transpose(n, m, testMatrix);
  print_matrix(m, n, testMatrix_t);
  clear(m, testMatrix_t);

   // </transpose()>


   // <product()>
  print_section("product");

  float** testMatrix_1 = matrix(n, m);
  float** testMatrix_2 = matrix(n, m);

  init_random_matrix(n, m, testMatrix_1);
  init_random_matrix(n, m, testMatrix_2);

  float** testMatrix_2_t = transpose(n, m, testMatrix_2);
  clear(n, testMatrix_2);

  print_matrix(n, m, testMatrix_1);
  print_matrix(m, n, testMatrix_2_t);

  float** testMatrix_p = product(n, m, m, n, testMatrix_1, testMatrix_2_t);
  clear(n, testMatrix_1);
  clear(m, testMatrix_2_t);
  
  print_matrix(n, n, testMatrix_p);
  clear(n, testMatrix_p);
   // </product()>
}

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

void print_section(char s[]) {
  printf("\n\n---------%s()---------\n", s);
}
