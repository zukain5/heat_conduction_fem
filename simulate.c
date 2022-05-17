#include "1dim_fem.h"
#include "utility.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
    fem_parameter fem;
    fem.NE = 300;
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

    int series_num = 10;
    double params[1] = {0};

    FILE *fp;
    if ((fp = fopen("SNAPSHOT", "w")) == NULL){
        printf("Cannot open SNAPSHOT.");
        exit(0);
    }

    for (int i=0; i<series_num; i++){
        params[0] = i+1;
        double Q[N+1] = {0};
        calc_Q_from_fucntion(Q_const, fem.NE, Q, x, params);

        fem.Q = &Q;

        double ans[N+1] = {0};
        fem_solver(ans, fem, bound);
        for (int j=0; j<=fem.NE; j++){
            fprintf(fp, "%lf\n", ans[j]);
        }
    }

    fclose(fp);

    return 0;
}
