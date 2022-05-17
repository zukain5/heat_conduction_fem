#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include "define.h"

/**
 * @fn
 * 連立方程式を標準出力する
 * @param (eq) 連立方程式の係数を取り出した2次元配列
 * @param (n) 連立方程式の式の数
 */
void print_eq(double eq[][N+1], int n){
    for (int i=0; i<n; i++){
        for (int j=0; j<n+1; j++){
            printf("%6.1lf ", eq[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

double _max(double l[N], int n){
    double max_value = l[0];
    for (int i=1; i<n; i++){
        if (l[i]>max_value){
            max_value = l[i];
        }
    }
    
    return max_value;
}

double _min(double l[N], int n){
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

    fprintf(gp, "set xrange [%lf:%lf]\n", _min(x, n), _max(x, n));
    fprintf(gp, "set yrange [%lf:%lf]\n", _min(y, n), _max(y, n));
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
