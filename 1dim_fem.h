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

void fem_solver(double ans[N+1], fem_parameter fem, boundary_condition bound);
