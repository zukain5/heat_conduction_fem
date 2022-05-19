#include "1dim_fem.h"
#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
    // 入力
    FILE *fp_settings;
    if ((fp_settings = fopen("SETTINGS", "r")) == NULL){
        printf("Cannot open SETTINGS.");
        exit(0);
    }

    fem_parameter fem;
    fscanf(fp_settings, "%d %lf %lf %lf", &fem.NE, &fem.length, &fem.A, &fem.lambda);

    boundary_condition bound;
    fscanf(fp_settings, "%d %d %lf %lf", &bound.type_min, &bound.type_max, &bound.value_min, &bound.value_max);

    int params_count;
    fscanf(fp_settings, "%d", &params_count);

    double params_range[PARAMS_MAX][3] = {0};
    for (int i=0; i<params_count; i++){
        fscanf(fp_settings, "%lf %lf %lf", &params_range[i][0], &params_range[i][1], &params_range[i][2]);
    }

    double sample_rate;
    int basis_count;
    fscanf(fp_settings, "%lf %d", &sample_rate, &basis_count);

    fclose(fp_settings);

    // 入力ここまで

    double x[N+1] = {0};
    for (int i=0; i<=fem.NE; i++){
        x[i] = fem.length / fem.NE * i;
    }

    double params_all[SERIES_MAX][PARAMS_MAX] = {0};
    int series_num = generate_params_linear(params_count, params_all, params_range);

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

    for (int j=0; j<params_count; j++){
        fprintf(fp_outputall, "param%d,", j+1);
    }

    for (int j=0; j<=fem.NE; j++){
        fprintf(fp_outputall, "value%d", j+1);
        if (j != fem.NE){
            fprintf(fp_outputall, ",");
        }
    }

    fprintf(fp_outputall, "\n");

    for (int i=0; i<series_num; i++){
        double params[PARAMS_MAX] = {0};
        for (int j=0; j<params_count; j++){
            params[j] = params_all[i][j];
        }
        double Q[N+1] = {0};
        calc_Q_from_fucntion(Q_normal_dist, fem.NE, Q, x, params);

        // if (i==250){
        //     for (int j=0; j<=fem.NE; j++){
        //         printf("%lf\n", Q[j]);
        //     }
        // }

        fem.Q = &Q;

        double ans[N+1] = {0};
        fem_solver(ans, fem, bound);
        for (int j=0; j<params_count; j++){
            fprintf(fp_outputall, "%lf,", params[j]);
        }
        for (int j=0; j<=fem.NE; j++){
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
