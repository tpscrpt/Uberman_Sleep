#ifndef UBERMAN_MATH_LOGREG_H_
#define UBERMAN_MATH_LOGREG_H_

#include <stdlib.h>
#include <math.h>

extern void logreg(
  Matrix * X,   // data
  Matrix * Y,   // labels
  Matrix * W,   // weights
  float  * b,   // intercept
  int      m,   // samples
  int      nx,  // features
  float    a    // learning rate
);

extern Matrix * forward_pass(Matrix * X, Matrix * W, float b);
extern float compute_cost(Matrix * A, Matrix * Y);
extern Matrix * compute_dZ(Matrix * A, Matrix * Y);
extern Matrix * compute_dW(Matrix * X, Matrix * dZ);
extern float compute_db(Matrix * dZ); 
extern void update_W(Matrix * W, Matrix * dW, float learning_rate);
extern void update_b(float * b, float db, float learning_rate);

extern float ** predict(
  float ** X,
  float ** w,
  float    b,
  int      nx,
  int      m
);

#endif