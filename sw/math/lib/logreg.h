#ifndef UBERMAN_MATH_LOGREG_H_
#define UBERMAN_MATH_LOGREG_H_

#include <stdlib.h>
#include <math.h>

extern float logreg(
  float ** X,   // data
  float ** Y,   // labels
  float ** w,   // weights
  float  * b,   // intercept
  int      m,   // samples
  int      nx,  // features
  float    a    // learning rate
);

/* logreg() executes the following calls, in order */
extern float ** activation(float ** w, float ** X, int nx, int m, float b);
extern float ** loss(float * A, float * Y, int m);
extern float    cost(float * L, int m);
extern float ** derive_weights(float ** X, float * A, float * Y, int m, int nx);
extern float    derive_intercept(float * A, float * Y, int m);
extern void     update(float ** w, float * b, float ** dw, float db, int nx, float a);

#endif