#pragma once
#include "define.h"
typedef struct {
    int NE;
    double length;
    double A;
    double lambda;
    double *Q;
} fem_parameter;

typedef struct {
    // 境界条件
    int type_min; // 0が基本・1が自然
    int type_max; // 0が基本・1が自然
    double value_min;
    double value_max;
} boundary_condition;

#ifdef __cplusplus
extern "C" {
    extern int _select_pivot(double eq[][N+1], int n, int j);
    extern void _swap_row(double eq[][N+1], int n, int pivot_i, int diagonal_i);
    extern void _normalize_row(double eq[][N+1], int n, int diagonal_i);
    extern void _subtract_row(double eq[][N+1], int n, int diagnoal_i);
    extern void _solve_equations(double eq[][N+1], int n, double ans[N]);
}
#endif  // __cplusplus

void fem_solver(double ans[N+1], fem_parameter fem, boundary_condition bound);
