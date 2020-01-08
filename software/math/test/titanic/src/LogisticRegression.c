// https://github.com/yusugomori/DeepLearning/blob/master/c/LogisticRegression.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LogisticRegression.h"

void test_lr(void);


void LogisticRegression__construct(LogisticRegression *logreg, int N, int n_in, int n_out) {
  int i, j;
  logreg->N = N;
  logreg->n_in = n_in;
  logreg->n_out = n_out;

  logreg->W = (float **)malloc(sizeof(float*) * n_out);
  logreg->W[0] = (float *)malloc(sizeof(float) * n_in * n_out);
  for(i=0; i<n_out; i++) logreg->W[i] = logreg->W[0] + i * n_in;
  logreg->b = (float *)malloc(sizeof(float) * n_out);

  for(i=0; i<n_out; i++) {
    for(j=0; j<n_in; j++) {
      logreg->W[i][j] = 0;
    }
    logreg->b[i] = 0;
  }
}

void LogisticRegression__destruct(LogisticRegression *logreg) {
  free(logreg->W[0]);
  free(logreg->W);
  free(logreg->b);
}

void LogisticRegression_train(LogisticRegression *logreg, float *x, int *y, float lr) {
  int i,j;
  float *p_y_given_x = (float *)malloc(sizeof(float) * logreg->n_out);
  float *dy = (float *)malloc(sizeof(float) * logreg->n_out);

  for(i=0; i<logreg->n_out; i++) {
    p_y_given_x[i] = 0;
    for(j=0; j<logreg->n_in; j++) {
      p_y_given_x[i] += logreg->W[i][j] * x[j];
    }
    p_y_given_x[i] += logreg->b[i];
  }
  LogisticRegression_softmax(logreg, p_y_given_x);

  for(i=0; i<logreg->n_out; i++) {
    dy[i] = y[i] - p_y_given_x[i];

    for(j=0; j<logreg->n_in; j++) {
      logreg->W[i][j] += lr * dy[i] * x[j] / logreg->N;
    }

    logreg->b[i] += lr * dy[i] / logreg->N;
  }

  free(p_y_given_x);
  free(dy);
}

void LogisticRegression_sigmoid(LogisticRegression *logreg, float *x) {

}

void LogisticRegression_softmax(LogisticRegression *logreg, float *x) {
  int i;
  float max = 0.0;
  float sum = 0.0;

  for(i=0; i<logreg->n_out; i++) if(max < x[i]) max = x[i];
  for(i=0; i<logreg->n_out; i++) {
    x[i] = exp(x[i] - max);
    sum += x[i];
  }

  for(i=0; i<logreg->n_out; i++) x[i] /= sum;
}

void LogisticRegression_predict(LogisticRegression *logreg, float *x, float *y) {
  int i,j;

  for(i=0; i<logreg->n_out; i++) {
    y[i] = 0;
    for(j=0; j<logreg->n_in; j++) {
      y[i] += logreg->W[i][j] * x[j];
    }
    y[i] += logreg->b[i];
  }

  LogisticRegression_softmax(logreg, y);
}



/*

void test_lr(void) {
  int i, j, epoch;

  double learning_rate = 0.1;
  int n_epochs = 500;

  int train_N = 6;
  int test_N = 2;
  int n_in = 6;
  int n_out = 2;


  // training data
  int train_X[train_N][n_in] = {
    {1, 1, 1, 0, 0, 0},
    {1, 0, 1, 0, 0, 0},
    {1, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 0},
    {0, 0, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 0}
  };

  int train_Y[train_N][n_out] = {
    {1, 0},
    {1, 0},
    {1, 0},
    {0, 1},
    {0, 1},
    {0, 1}
  };


  // construct LogisticRegression
  LogisticRegression classifier;
  LogisticRegression__construct(&classifier, train_N, n_in, n_out);


  // train
  for(epoch=0; epoch<n_epochs; epoch++) {
    for(i=0; i<train_N; i++) {
      LogisticRegression_train(&classifier, train_X[i], train_Y[i], learning_rate);
    }
    // learning_rate *= 0.95;
  }


  // test data
  int test_X[test_N][n_in] = {
    {1, 0, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 0}
  };

  double test_Y[test_N][n_out];


  // test
  for(i=0; i<test_N; i++) {
    LogisticRegression_predict(&classifier, test_X[i], test_Y[i]);
    for(j=0; j<n_out; j++) {
      printf("%f ", test_Y[i][j]);
    }
    printf("\n");
  }



  // destruct LogisticRegression
  LogisticRegression__destruct(&classifier);
}




int main(void) {
  test_lr();
  
  return 0;
}

*/