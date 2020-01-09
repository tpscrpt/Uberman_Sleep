#ifndef UBERMAN_MATH_MATRIX_H_
#define UBERMAN_MATH_MATRIX_H_

#include <stdlib.h>
#include <math.h>

typedef struct Matrix {
  int n, m;
  float ** d;
} Matrix;

extern Matrix * matrix(int n, int m);
extern Matrix * transpose(Matrix * X);
extern Matrix * product(Matrix * A, Matrix * B);

extern void sigmoid(Matrix * X);
extern void bump(Matrix * X, float b);
extern void init_val(Matrix * X, float val);
extern void clear(Matrix * X);


#endif

/* Sources: 
    1. <https://github.com/gregdhill/lin-reg/blob/master/lreg.c> */
