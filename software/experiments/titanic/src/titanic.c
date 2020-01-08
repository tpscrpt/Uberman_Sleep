//train_cleaned = np.loadtxt("output/train_cleaned.csv", dtype=float, skiprows=1, delimiter=',')
//test_cleaned = np.loadtxt("output/test_cleaned.csv", dtype=float, skiprows=1, delimiter=',')

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "csv.h"
#include "LogisticRegression.h"

static int ** alloc_mati(int m, int n);
static float ** alloc_matf(int m, int n);

void cleari(int n, int** X);
void clearf(int n, float** X);

int main () {
  FILE * train = fopen("output/train_cleaned.csv", "r");

  if (csvgetline(train) == NULL) {
    return printf("Exiting due to bad file");
  }

  int i, j, epoch;

  double learning_rate = 0.1;
  int n_epochs = 500;

  int n_out = 1;
  int n_in = csvnfield() - 1;

  int N = 714;
  float ratio = 0.1;

  int train_N = N * ratio;
  int dev_N = N * (1 - ratio);

  if (dev_N + train_N < N) train_N ++;

  float ** train_X = alloc_matf(train_N, n_in);   // (train_N * ratio, n_in)
  float ** train_Y = alloc_matf(train_N, n_out);  // (train_N * ratio, n_out)

  float ** dev_X = alloc_matf(dev_N, n_in);       // (dev_N * (1 - ratio), n_in)
  float ** dev_Y = alloc_matf(dev_N, n_out);      // (dev_N * (1 - ratio), n_out)


  printf("train_N, dev_N: %d, %d", train_N, dev_N);

  for (i = 0; csvgetline(train) != NULL; i ++) {
    int update_dev = i >= train_N;
    int index = update_dev ? i - train_N : i;

    float ** update_X = update_dev ? dev_X : train_X;
    float ** update_Y = update_dev ? dev_Y : train_Y;

    int survived = atoi(csvfield(0));
    update_Y[index][0] = survived ? 1 : 0;

    printf("%f   ", update_Y[index][0]);

    for (j = 0; j < n_in; j ++) {
      update_X[index][j] = atof(csvfield(j));
      printf("%f ", update_X[index][j]);
    }
    printf("\n");
  }

  LogisticRegression classifier;
  LogisticRegression__construct(&classifier, train_N, n_in, n_out);

  for (epoch = 0; epoch < n_epochs; epoch ++) {
    for (i = 0; i < train_N; i ++) {
      LogisticRegression_train(&classifier, train_X[i], train_Y[i], learning_rate);
    }
  }

  float ** dev_P = alloc_matf(dev_N, n_out);
  int accurate = 0;

  for (i = 0; i < dev_N; i ++) {
    LogisticRegression_predict(&classifier, dev_X[i], dev_P[i]);
  }

  clearf(train_N, train_X);
  clearf(train_N, train_Y);
  clearf(dev_N, dev_X);
  clearf(dev_N, dev_Y);

  printf("dev_N: %d", dev_N);
  printf("accurate: %d", accurate);
}


static int ** alloc_mati(int n, int m) {
  int **X;
  X = (int **) malloc(n * sizeof (*X));

  for (int i=0; i<n; i++)
    X[i] = (int *) malloc(m * sizeof(*X[i]));

  return X;
}
static float ** alloc_matf(int n, int m) {
  float **X;
  X = (float **) malloc(n * sizeof (*X));

  for (int i=0; i<n; i++)
    X[i] = (float *) malloc(m * sizeof(*X[i]));

  return X;
}

void cleari(int n, int** X){
  for (int i=0; i<n; i++)
    free(X[i]);
  free(X);
}
void clearf(int n, float** X){
  for (int i=0; i<n; i++)
    free(X[i]);
  free(X);
}