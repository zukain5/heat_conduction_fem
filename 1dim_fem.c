#include "1dim_fem.h"
#include <stdio.h>
#include <stdlib.h>
#include "define.h"

void _calc_equations(double eq[][N+1], fem_parameter fem, boundary_condition bound){
    double L = fem.length / fem.NE;
    for (int i=0; i<fem.NE; i++){
        // K
        double k_abs = fem.lambda * fem.A / L;
        eq[i][i] += k_abs;
        eq[i][i+1] -= k_abs;
        eq[i+1][i] -= k_abs;
        eq[i+1][i+1] += k_abs;
        
        // f
        eq[i][fem.NE+1] += fem.A * L * (2 * fem.Q[i] + fem.Q[i+1]) / 6;
        eq[i+1][fem.NE+1] += fem.A * L * (fem.Q[i] + 2 * fem.Q[i+1]) / 6;
    }

    int n = fem.NE+1;

    if (bound.type_min == 0){
        eq[0][0] = 1;
        for (int j=1; j<n; j++){ eq[0][j] = 0; }
        eq[0][n] = bound.value_min;
    }

    if (bound.type_max == 0){
        eq[n-1][n-1] = 1;
        for (int j=0; j<n-1; j++){ eq[n-1][j] = 0; }
        eq[n-1][n] = bound.value_max;
    }

    if (bound.type_min == 1){
        eq[0][n] += fem.lambda * fem.A * bound.value_min;
    }

    if (bound.type_max == 1){
        eq[n-1][n] += fem.lambda * fem.A * bound.value_max;
    }
}

int _select_pivot(double eq[][N+1], int n, int j){
    double abs[n];

    for (int i=j; i<n; i++){
        abs[i] = eq[i][j] * eq[i][j];
    }

    double max = abs[j];
    int pivot_i = j;
    for (int i=j+1; i<n; i++){
        if (abs[i]>max){
            max = abs[i];
            pivot_i = i;
        }
    }

    if (max == 0){
        printf("解が一意に定まりません。");
        exit(0);
    }

    return pivot_i;
}

void _swap_row(double eq[][N+1], int n, int pivot_i, int diagonal_i){
    if (pivot_i == diagonal_i){return;}

    for (int j=0; j<n+1; j++){
        double temp = eq[diagonal_i][j];
        eq[diagonal_i][j] = eq[pivot_i][j];
        eq[pivot_i][j] = temp;
    }
}

void _normalize_row(double eq[][N+1], int n, int diagonal_i){
    double divisor = eq[diagonal_i][diagonal_i];
    for (int j=0; j<n+1; j++){
        eq[diagonal_i][j] /= divisor;
    }
}

void _subtract_row(double eq[][N+1], int n, int diagnoal_i){
    for (int i=0; i<n+1; i++){
        if (i == diagnoal_i){continue;}
        double magnification = eq[i][diagnoal_i];
        for (int j=0; j<n+1; j++){
            eq[i][j] -= eq[diagnoal_i][j] * magnification;
        }
    }
}

void _solve_equations(double eq[][N+1], int n, double ans[N]){
    // 1列ずつ消去していく
    for (int j=0; j<n; j++){
        int pivot_i = _select_pivot(eq, n, j);
        _swap_row(eq, n, pivot_i, j);
        _normalize_row(eq, n, j);
        _subtract_row(eq, n, j);
    }

    for (int i=0; i<n; i++){
        ans[i] = eq[i][n];
    }
}

void fem_solver(double ans[N+1], fem_parameter fem, boundary_condition bound){
    double eq[N][N+1] = {0};
    _calc_equations(eq, fem, bound);
    _solve_equations(eq, fem.NE+1, ans);
}
