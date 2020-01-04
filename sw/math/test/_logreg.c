#include "../lib/logreg.h"
#include "../lib/matrix.h"
#include "../lib/test/testing.h"

static void test() {
  int m  = 5; // # of examples
  int nx = 3; // # of features per example

  float a = 0.01; // learning rate

  float ** w = matrix(nx, 1);     // (nx, 1), column vector
    init_random_matrix(nx, 1, w);

  float ** X = matrix(nx, m);     // (nx, m), matrix
    init_random_matrix(nx, m, X);

  float ** Y = matrix(1, m); // ground truth labels
    for (int i = 0; i < m; i ++)
      Y[0][i] = rand() > rand() ? 0.0 : 1.0;

  float b = 0.0983; // (1, 1), constant

  print_matrix(nx, 1, w, "w initial:\n");
  print_matrix(nx, m, X, "X initial:\n");
  print_matrix(1, m,  Y, "Y initial:\n");
  printf(                "b initial: %f\n", b);

  float ** A  = activation(w, X, nx, m, b);
  print_matrix(1, m, A, "A:\n");

  float ** L  = loss(A[0], Y[0], m);
  print_matrix(1, m, L, "L:\n");

  float tsoc  = cost(L[0], m);
  printf("cost: %f\n\n", tsoc);

  float ** dw = derive_weights(X, A[0], Y[0], m, nx);
  print_matrix(nx, 1, dw, "dw derivatives:\n");

  float    db = derive_intercept(A[0], Y[0], m);
  printf("db derivative: %f\n\n", db);

  update(w, &b, dw, db, nx, a);

  print_matrix(nx, 1, w, "w updated:\n");
  printf("b updated: %f\n\n", b);

  clear(nx, w);
  clear(nx, X);
  clear(1, Y);
  clear(1, A);
  clear(1, L);
  clear(nx, dw);
}

void main() { test(); }