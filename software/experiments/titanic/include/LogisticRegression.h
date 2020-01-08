// https://github.com/yusugomori/DeepLearning/blob/master/c/LogisticRegression.h

#ifndef LOGISTICREGRESSION_H
#define LOGISTICREGRESSION_H

typedef struct {
  int N;        // Number of examples
  int n_in;     // Number of features per example
  int n_out;    // Number of categories to predict from
  float **W;   // Weights
  float *b;    // Bias
} LogisticRegression;

void LogisticRegression__construct(LogisticRegression*, int, int, int);
void LogisticRegression__destruct(LogisticRegression*);
void LogisticRegression_train(LogisticRegression*, float*, int*, float);
void LogisticRegression_softmax(LogisticRegression*, float*);
void LogisticRegression_sigmoid(LogisticRegression*, float*);
void LogisticRegression_predict(LogisticRegression*, float*, float*);

#endif