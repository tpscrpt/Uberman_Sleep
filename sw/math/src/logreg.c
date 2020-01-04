#include "../lib/matrix.h"
#include "../lib/logreg.h"

float logreg(
  float ** X,   // data
  float ** Y,   // labels
  float ** w,   // weights
  float  * b,   // intercept
  int      m,   // samples
  int      nx,  // features
  float    a    // learning rate
) {
  float ** A  = activation(w, X, nx, m, *b);
  float ** L  = loss(A[0], Y[0], m);
  float tsoc  = cost(L[0], m);

  float ** dw = derive_weights(X, A[0], Y[0], m, nx);
  float    db = derive_intercept(A[0], Y[0], m);

  update(w, b, dw, db, nx, a);

  return tsoc;
}

float ** activation(float ** w, float ** X, int nx, int m, float b) {
  float ** wT = transpose(nx, 1, w);

  float ** wT_X = product(1, nx, nx, m, wT, X); // (1, m) -- z
  clear(1, wT);

  bump(1, m, wT_X, b);
  sigmoid(1, m, wT_X);
  
  return wT_X;
}

float ** loss(float * A, float * Y, int m) {
  float ** L = matrix(1, m);

  for (int i = 0; i < m; i ++) {
    float a = A[i];
    int   y = Y[i];
    
    L[0][i] = (y * log(a)) - ((1.0 - y) * log(1.0 - a));
  }

  return L;
}

float cost(float * L, int m) {
  float total_loss = 0;

  for (int i = 0; i < m; i ++)
    total_loss += L[i];

  return (-1.0 / m) * total_loss;
}

float ** derive_weights(float ** X, float * A, float * Y, int m, int nx) {
  float ** A_minus_Y = matrix(1, m); // (1, m) [0, 1, 0, 0, 1]

  for (int i = 0; i < m; i ++)
    A_minus_Y[0][i] = A[i] - Y[i];
  
  float ** A_minus_Y_T = transpose(1, m, A_minus_Y); // (m, 1)
  clear(1, A_minus_Y);

  float ** X_A_minus_Y_T = product(nx, m, m, 1, X, A_minus_Y_T); // (nx, 1)
  clear(m, A_minus_Y_T);

  for (int i = 0; i < nx; i ++)
    X_A_minus_Y_T[i][0] *= -1.0 / m;

  return X_A_minus_Y_T;
}

float derive_intercept(float * A, float * Y, int m) {
  float sum = 0;

  for (int i = 0; i < m; i ++)
    sum += (1.0 / m) * (A[i] - Y[i]);

  return sum;
}

void update(float ** w, float * b, float ** dw, float db, int nx, float a) {
  for (int i = 0; i < nx; i ++)
    w[i][0] -= (a * dw[i][0]);

  *b -= (a * db);
}