#include "1dim_fem.h"
#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
    fem_parameter fem;
    fem.NE = 100;
    fem.length = 4.0;
    fem.A = 1.0;
    fem.lambda = 1.0;

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

    int params_count = 1;

    double params_all[SERIES_MAX][PARAMS_MAX] = {0};
    double params_range[][3] = {
        {0.0, 1.0, 100},
    };

    int series_num = generate_params_linear(params_count, params_all, params_range);
    double sample_rate = 0.1;

    FILE *fp_snapshot;
    if ((fp_snapshot = fopen("SNAPSHOT", "w")) == NULL){
        printf("Cannot open SNAPSHOT.");
        exit(0);
    }

    FILE *fp_outputall;
    if ((fp_outputall = fopen("OUTPUTALL.csv", "w")) == NULL){
        printf("Cannot open OUTPUTALL.csv.");
        exit(0);
    }

    int sample_count = 0;

    for (int i=0; i<series_num; i++){
        double params[PARAMS_MAX] = {0};
        for (int j=0; j<params_count; j++){
            params[j] = params_all[i][j];
        }
        double Q[N+1] = {0};
        calc_Q_from_fucntion(Q_const, fem.NE, Q, x, params);

        fem.Q = &Q;

        double ans[N+1] = {0};
        fem_solver(ans, fem, bound);
        for (int j=0; j<=fem.NE; j++){
            for (int k=0; k<params_count; k++){
                // fprintf(fp_outputall, "%lf,", params[k]);
            }
            fprintf(fp_outputall, "%lf", ans[j]);
            if (j != fem.NE){
                fprintf(fp_outputall, ",");
            }
        }
        fprintf(fp_outputall, "\n");

        if (floor(i*sample_rate) > floor((i-1)*sample_rate)){
            sample_count++;
            for (int j=0; j<=fem.NE; j++){
                fprintf(fp_snapshot, "%lf\n", ans[j]);
            }            
        }
    }

    int basis_count = 1;

    FILE *fp_parameters;
    if ((fp_parameters = fopen("PARAMETERS", "w")) == NULL){
        printf("Cannot open PARAMETERS.");
        exit(0);
    }

    fprintf(fp_parameters, "%d\n%d\n%d\n", fem.NE+1, sample_count, basis_count);

    fclose(fp_snapshot);
    fclose(fp_outputall);
    fclose(fp_parameters);

    return 0;
}
