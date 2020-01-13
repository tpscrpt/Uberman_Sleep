#ifndef UBERMAN_MATH_MATRIX_H_
#define UBERMAN_MATH_MATRIX_H_

#include <stdlib.h>
#include <math.h>

typedef struct Matrix {
  int n, m;
  float ** d;
} Matrix;

extern void clear(Matrix * X);
extern Matrix * matrix(int n, int m);
extern Matrix * copy_matrix(Matrix * X);
extern Matrix * transpose(Matrix * X);
extern Matrix * product(Matrix * A, Matrix * B);
extern Matrix * matrix_sum(Matrix * X);

extern void sigmoid(Matrix * X);
extern void relu(Matrix * X, float a);
extern void bump(Matrix * X, float b);
extern void bump_vector(Matrix * X, Matrix * b);
extern void frac(Matrix * X, float m);
extern void init_matrix(Matrix * X, float val);
extern void init_matrix_random(Matrix * X);


#endif

/* Sources: 
    1. <https://github.com/gregdhill/lin-reg/blob/master/lreg.c> */
