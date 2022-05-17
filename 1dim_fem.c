#include <stdio.h>
#include <stdlib.h>
#include "1dim_fem.h"

typedef double(* Q_FUNC)(double, double *);

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

void print_eq(double eq[][N+1], int n){
    for (int i=0; i<n; i++){
        for (int j=0; j<n+1; j++){
            printf("%6.1lf ", eq[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void calc_equations(double eq[][N+1], fem_parameter fem, boundary_condition bound){
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

void solve_equations(double eq[][N+1], int n, double ans[N]){
    // 1列ずつ消去していく
    for (int j=0; j<n; j++){
        int pivot_i = select_pivot(eq, n, j);
        swap_row(eq, n, pivot_i, j);
        normalize_row(eq, n, j);
        subtract_row(eq, n, j);
    }

    for (int i=0; i<n; i++){
        ans[i] = eq[i][n];
        printf("%lf\n", ans[i]);
    }
}

double max(double l[N], int n){
    double max_value = l[0];
    for (int i=1; i<n; i++){
        if (l[i]>max_value){
            max_value = l[i];
        }
    }
    
    return max_value;
}

double min(double l[N], int n){
    double min_value = l[0];
    for (int i=1; i<n; i++){
        if (l[i]<min_value){
            min_value = l[i];
        }
    }
    
    return min_value;
}

void visualize(double x[N+1], double y[N+1], int n){
    FILE *gp;
    if ((gp = popen("gnuplot -persist", "w")) == NULL) {
        printf("Can't open gnuplot.");
        exit(0);
    }

    fprintf(gp, "set xrange [%lf:%lf]\n", min(x, n), max(x, n));
    fprintf(gp, "set yrange [%lf:%lf]\n", min(y, n), max(y, n));
    fprintf(gp, "set xlabel \"x\"\n");
    fprintf(gp, "set ylabel \"Temperature\"\n");
    fprintf(gp, "plot '-' with lines linetype 1 title \"Temperature\"\n");

    for (int i=0; i<n; i++){
        fprintf(gp, "%lf\t%lf\n", x[i], y[i]);
    }

    if (pclose(gp) == EOF) {
        printf("Can't close gnuplot.");
        exit(0);
    }
}

void calc_Q_from_fucntion(Q_FUNC pfunc, int NE, double Q[N+1], double x[N], double *params){
    for (int i=0; i<=NE; i++){
        Q[i] = pfunc(x[i], params);
    }
}

double Q_const(double x, double *params){
    double constant = params[0];
    return constant;
}

double Q_linear(double x, double *params){
    double coefficient = params[0];
    return coefficient * x;
}

void fem_solver(double ans[N+1], fem_parameter fem, boundary_condition bound){
    double eq[N][N+1] = {0};
    calc_equations(eq, fem, bound);
    solve_equations(eq, fem.NE+1, ans);
}

int main(void){
    fem_parameter fem;
    fem.NE = 300;
    fem.length = 4.0;
    fem.A = 1.0;
    fem.lambda = 1.0;

    double Q[N+1] = {0};

    // 境界条件
    boundary_condition bound;
    bound.type_min = 0; // 0が基本・1が自然
    bound.type_max = 1; // 0が基本・1が自然
    bound.value_min = 0;
    bound.value_max = 0;

    double x[N+1] = {0};
    for (int i=0; i<=fem.NE; i++){
        x[i] = fem.length / fem.NE * i;
    }

    double params[] = {1};
    calc_Q_from_fucntion(Q_linear, fem.NE, Q, x, params);

    fem.Q = &Q;

    double ans[N+1] = {0};
    fem_solver(ans, fem, bound);

    visualize(x, ans, fem.NE+1);

    return 0;
}
