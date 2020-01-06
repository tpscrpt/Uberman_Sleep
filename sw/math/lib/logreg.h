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

extern float ** predict(
  float ** X,
  float ** w,
  float    b,
  int      nx,
  int      m
);

#endif