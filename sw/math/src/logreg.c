#include "../lib/matrix.h"
#include "../lib/logreg.h"

// TODO use int matrices for Y vectors to reduce FPU dependency
// TODO implement learning rate decay

float logreg(
  float ** X,   // data           (nx, m)
  float ** Y,   // labels         (1, m)
  float ** w,   // weights        (nx, 1)
  float  * b,   // intercept      scalar
  int      m,   // samples        scalar
  int      nx,  // features       scalar
  float    a    // learning rate  scalar
) {

  // Forward Propagation
  float ** A  = activation(w, X, nx, m, *b);  // (1, m) A = σ(wT * X + b)
  float ** L  = loss(A[0], Y[0], m);          // (1, m) L = Ylog(a) - (1 - Y) * log(1 - A)
  float tsoc  = cost(L[0], m);                // scalar cost = -1/m * sum(L)

  // Backward propagation
  float ** dw = derive_weights(X, A[0], Y[0], m, nx); // (nx, 1) derivative of each feature weight
  float    db = derive_intercept(A[0], Y[0], m);      // scalar derivative of intercept/bias

  // Gradient descent
  update(w, b, dw, db, nx, a);

  return tsoc;
}

float ** predict(float ** X, float ** w, float b, int nx, int m) {
  float ** Y_prediction = matrix(1, m);
  float ** A = activation(w, X, nx, m, b);

  for (int i = 0; i < m; i ++)
    Y_prediction[0][m] = A[0][m] <= 0.5 ? 0.0 : 1.0;

  return Y_prediction;
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