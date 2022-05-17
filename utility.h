#pragma once
#include "define.h"

typedef double(* Q_FUNC)(double, double *);

void print_eq(double eq[][N+1], int n);
void visualize(double x[N+1], double y[N+1], int n);
void calc_Q_from_fucntion(Q_FUNC pfunc, int NE, double Q[N+1], double x[N], double *params);
double Q_const(double x, double *params);
double Q_linear(double x, double *params);
