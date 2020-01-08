#ifndef UBERMAN_MATH_MATRIX_H_
#define UBERMAN_MATH_MATRIX_H_

#include <stdlib.h>
#include <math.h>

extern void sigmoid(int n, int m, float ** X);
extern void bump(int n, int m, float ** X, float b);

/* <https://github.com/gregdhill/lin-reg/blob/master/lreg.c> */
extern float** matrix(int n, int m);
extern void clear(int n, float** X);
extern float** transpose(int n, int m, float** X);
extern float** product(int n, int m, int p, int q, float** A, float** B);
/* </https://github.com/gregdhill/lin-reg/blob/master/lreg.c> */

#endif