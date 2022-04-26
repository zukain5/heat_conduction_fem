#include <stdio.h>
#include <stdlib.h>
#include "1dim_fem.h"

void print_eq(double eq[][N+1], int n){
    for (int i=0; i<n; i++){
        for (int j=0; j<n+1; j++){
            printf("%6.1lf ", eq[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void calc_equations(double eq[][N+1], int NE, double L, double Q, double A, double lambda){
    for (int i=0; i<NE; i++){
        // K
        double k_abs = lambda * A / L;
        eq[i][i] += k_abs;
        eq[i][i+1] -= k_abs;
        eq[i+1][i] -= k_abs;
        eq[i+1][i+1] += k_abs;
        
        // f
        double f_abs = Q * A * L / 2;
        eq[i][NE+1] += f_abs;
        eq[i+1][NE+1] += f_abs;
    }
}

int select_pivot(double eq[][N+1], int n, int j){
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

void swap_row(double eq[][N+1], int n, int pivot_i, int diagonal_i){
    if (pivot_i == diagonal_i){return;}

    for (int j=0; j<n+1; j++){
        double temp = eq[diagonal_i][j];
        eq[diagonal_i][j] = eq[pivot_i][j];
        eq[pivot_i][j] = temp;
    }
}

void normalize_row(double eq[][N+1], int n, int diagonal_i){
    double divisor = eq[diagonal_i][diagonal_i];
    for (int j=0; j<n+1; j++){
        eq[diagonal_i][j] /= divisor;
    }
}

void subtract_row(double eq[][N+1], int n, int diagnoal_i){
    for (int i=0; i<n+1; i++){
        if (i == diagnoal_i){continue;}
        double magnification = eq[i][diagnoal_i];
        for (int j=0; j<n+1; j++){
            eq[i][j] -= eq[diagnoal_i][j] * magnification;
        }
    }
}

void solve_equations(double eq[][N+1], int n){
    // 1列ずつ消去していく
    for (int j=0; j<n; j++){
        int pivot_i = select_pivot(eq, n, j);
        swap_row(eq, n, pivot_i, j);
        normalize_row(eq, n, j);
        subtract_row(eq, n, j);
    }

    for (int i=0; i<n; i++){
        printf("%lf\n", eq[i][n]);
    }
}

int main(void){
    // 入力
    int NE = 6;
    double L = 1.0;
    double Q = 1.0;
    double A = 1.0;
    double lambda = 1.0;

    double eq[N][N+1] = {0};
    calc_equations(eq, NE, L, Q, A, lambda);
    solve_equations(eq, NE+1);

    return 0;
}