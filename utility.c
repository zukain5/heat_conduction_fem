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

double Q_devide_3(double x, double *params){
    double length = 4.0;
    if (x < length/3){
        return params[0]*x/(length/3);
    } else if (length/3 <= x && x <= 2*length/3){
        return params[0]*(2*length/3 - x)/(length/3) + params[1]*(x - length/3)/(length/3);
    } else {
        return params[1]*(length - x)/(length/3);
    }
}

int generate_params_linear(int params_count, double params_all[][PARAMS_MAX], double params_range[][3]){
    int loop[SERIES_MAX] = {0};
    int loop_max[SERIES_MAX] = {0};
    double step[PARAMS_MAX] = {0};

    for (int i=0; i<params_count; i++){
        double param_min = params_range[i][0];
        double param_max = params_range[i][1];
        double param_devide_count = params_range[i][2];
        loop_max[i] = param_devide_count + 1;
        step[i] = (param_max - param_min) / param_devide_count;
    }

    int series_count = 0;
    int i=0;
    while (1){
        for (int j=0; j<params_count; j++){
            params_all[series_count][j] = params_range[j][0] + step[j] * loop[j];
        }

        series_count++;

        for (i=0; i<params_count; i++){
            loop[i]++;
            if (loop[i]<loop_max[i]){
                break;
            }
            loop[i] = 0;
        }

        if (i == params_count){
            break;
        }
    }

    return series_count;
}
