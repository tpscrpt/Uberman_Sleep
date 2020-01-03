#include "./functions.h"
#include "./testing.h"

float compute(float ** w, float ** x,
              int      nx, int     i,
              float    b           );

float loss_function(float a, int y);

void main() {
  int m =  1; // # of examples
  int nx = 3; // # of features per example
  

  float ** w = matrix(1, nx);     // (nx, 1), column vector | Refactor into array?
    init_random_matrix(1, nx, w);

  float ** x = matrix(m, nx);     // (nx, m), matrix
    init_random_matrix(m, nx, x);

  int y[m]; // ground truth labels
  y[0] = 1;

  float b = 0.2; // (1, 1), constant

  int i = 0; // ith example

  float a = compute(w, x, nx, i, b);
  float loss = loss_function(a, y[i]);
  float cost = loss;

  printf("a: %f\ncost: %f", a, cost);
}

float compute(float ** w, float ** x, int nx, int i, float b) {
  float ** w_T = transpose(1, nx, w);
  clear(1, w);

  float ** w_Tx = product(nx, 1, 1, nx, w_T, x);
  print_matrix(nx, 1, w_T);
  print_matrix(1, nx, x);
  print_matrix(nx, nx, w_Tx);
  clear(nx, w_T);
  clear(1, x);

  bump(nx, nx, w_Tx, b);
  print_matrix(nx, nx, w_Tx);
  sigmoid(nx, nx, w_Tx);
  print_matrix(nx, nx, w_Tx);

  float a = average(nx, nx, w_Tx);
  clear(nx, w_Tx);

  return a;
}

float loss_function(float a, int y) {
  return (-y * log(a)) - ((1.0 - y) * log(1 - a));
}