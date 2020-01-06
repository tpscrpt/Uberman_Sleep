#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <errno.h>

#include "../../lib/matrix.h"
#include "../../lib/logreg.h"
#include "../../lib/csv.h"
#include "../../lib/test/testing.h"

int main() {
  FILE * train = fopen("./test/titanic/output/train_cleaned.csv", "r");
  FILE * test = fopen("./test/titanic/output/test_cleaned.csv", "r");
  FILE * weights = fopen("./test/titanic/output/weights.csv", "r");
  FILE * bias = fopen("./test/titanic/output/bias.txt", "r");

  if (csvgetline(train) == NULL || csvgetline(test) == NULL) {
    return printf("Exiting due to bad file");
  }
  int nx = csvnfield() - 2; // first col is ID, second is survival label

  int first_run = csvgetline(weights) == NULL;

  int batch_size = 10;
  float a = 0.01;


  int m = batch_size;

  float ** X = matrix(nx, m);
  float ** Y = matrix(1, m);
  float ** w = matrix(nx, 1);
  float    b;
  
  if (first_run) {
    init_random_matrix(nx, 1, w);
    b = 0.0;
  } 
  else {
    for (int i = 0; i < nx; i ++) {
      w[i][0] = atof(csvfield(i));
    }
    
    fscanf(bias, "%f", &b);
    printf("b: %f\n", b);
  }

  fclose(weights);
  fclose(bias);

  int i = 0;
  int j = 2;

  while(csvgetline(train) != NULL) {
    Y[0][i%batch_size] = (float) atof(csvfield(1)); // truth label stored in 2nd column

    for (j = 2; j < nx + 2; j ++) {
      X[j-2][i%batch_size] = (float) atof(csvfield(j));
    }
    
    if ((i+1) % batch_size == 0) {
      float cost = logreg(X, Y, w, &b, m, nx, a);
      if ((i+1) % 700 == 0) printf("\ncost: %f\n", cost);
    }

    i ++;
  }

  weights = fopen("./test/titanic/output/weights.csv", "w");
  for (int k = 0; k < nx; k ++) {
    printf("%f\n", w[k][0]);
    k == nx - 1 ? fprintf(weights, "%f", w[k][0]) : fprintf(weights, "%f,", w[k][0]);
  }
  fclose(weights);

  bias = fopen("./test/titanic/output/bias.txt", "w");
  fprintf(bias, "%f", b);
  fclose(bias);

  clear(nx, X);
  clear(1, Y);
  clear(nx, w);

  fclose(train);
  fclose(test);
}